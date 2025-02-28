using Posix; // This *should* work with --pkg posix or libc in meson.build
using GLib;

public class U7ThreadLoop : U7Object {
    private static Mutex main_lock = Mutex();
    private static U7ThreadLoop main_thread_loop = null;

    private Thread<void*> current_thread;
    private MainContext context;
    private MainLoop loop;
    private AsyncQueue<U7Dictionary> queue;
    private string _name;
    private static uint64 thread_creation_count = 100;
    private bool _is_active;
    private GLib.Mutex mutex;
    private int messageCount;

    public override string get_name() {return _name;}

    public int incrementMessageCount() {
        return ++messageCount;
    }
    public U7Dictionary try_pop() {
        return queue.try_pop();
    }
    public bool is_active {
        get {
            lock (mutex) {
                return _is_active;
            }
        }
        private set {
            lock (mutex) {
                _is_active = value;
            }
        }
    }

    public static U7ThreadLoop mainThreadLoop() {
        return main_thread_loop;
    }

    public virtual void threadEntry(U7PropertyList *info) {}
    public virtual void threadSetup() {}


    public override void publishOnThread(string name, U7Dictionary *info) {
        

        //GLib.stdout.printf("Items in queue: %d\n", (int)this.queue.length);  // Prints: "Items in queue: 2"
        this.queue.push(info);
        //GLib.stdout.printf("U7ThreadLoop|publishOnThread %s|\n", name);
        //GLib.stdout.printf("U7ThreadLoop[%"  + uint64.FORMAT +  "]|name %s\n", this.getThreadID(), name);

    }

    public Thread<void*> thread() {
        return current_thread;
    }
    
    public static uint64 getCurrentThreadID() {
        return u7_tls_get_thread_uint64_id();
    }

    public uint64 get_thread_id() {
        return u7_tls_get_thread_uint64_id();
    }

    public static void startMainEventLoop() {
        if (main_thread_loop == null) {

            GLib.stdout.printf("U7ThreadLoop startMainEventLoop()|missing main_thread_loop\n");

        } else {
            main_thread_loop.run();

        }
    }
    private void mainThreadSetup() {

        /*
            Note: Main thread setup does not involve detaching a thread,
                  but the main thread does have a loop, context and an 
                  async queue.
                    
        */
        this.current_thread = Thread.self<void*>();
        this._private_threadEntrySetup();
        this.threadEntrySetup();

        U7NotificationCenter cntr = U7NotificationCenter.default();
        cntr.subscribe("keyboard_input", this);

    }

    public new static void init() {

        u7_tls_set_thread_uint64_id(0);

        //GLib.stdout.printf("U7ThreadLoop init()\n");
        main_thread_loop = new U7MainEventLoop("U7MainThread");
        main_thread_loop.mainThreadSetup();
        
        //GLib.stdout.printf("U7ThreadLoop init()|main_thread_loop %p\n", main_thread_loop);
        //GLib.stdout.printf("U7ThreadLoop main_thread_loop.thread(): %p\n", main_thread_loop.thread());
        //GLib.stdout.printf("U7ThreadLoop main_lock: %p\n", &main_lock);
    }

    public U7ThreadLoop(string name) {
        base();
        _name = name;
        mutex = Mutex();

    }

    construct {

        this.queue = new AsyncQueue<U7Dictionary>();

    }
    
    

    protected bool process_messages() {
        while (queue.length() > 0) {

            U7Dictionary message = queue.try_pop();

            bool log_message = false;

            if (log_message) {
                string json = message.to_json_string();
                GLib.stdout.printf("%s|%" + uint64.FORMAT + "|process_messages: %s\n", this.get_name(), this.getThreadID(), json);
            }


            if (message != null) {

                if (message.value.has_key("publication_name")) {
                    string notification_name = ((U7String)message.value["publication_name"]).to_string();
                    if (log_message)
                        GLib.stdout.printf("U7ThreadLoop [%s]: Processing notification: %s\n", this.get_name(), notification_name);
                    this.invoke_method(notification_name, message);
                } else {
                    if (log_message)
                        GLib.stdout.printf("U7ThreadLoop [%s]: missing publication_name\n", this.get_name());


                }
            }
        }
        return true; // Keep the source active
    }

    private void _private_threadEntrySetup() {

        this.recordThreadID();
        this.current_thread = Thread.self<void*>();
        //this.context = new MainContext();
        //this.context.push_thread_default();
        //GLib.stdout.printf("U7ThreadLoop [%s]: _private_threadEntrySetup\n", this.get_name());

    }
    
    // Update threadEntrySetup to use the new source creation
    public virtual void threadEntrySetup() {
        this.loop = new MainLoop();

        // Use an Idle source to process the queue when the loop is idle
        GLib.Idle.add(() => {
            this.process_messages();
            return true; // Keep the idle source active
        });

        GLib.stdout.printf("U7ThreadLoop [%s]: threadEntrySetup\n", this.get_name());
    }


    public virtual void run() {

/*
        Timeout.add(1000, () => {
            GLib.stdout.printf("Event triggered in separate thread!\n");
            return true; // Return true to keep the timeout running
        });

*/      this.loop.run();
        bool loop_exists = (this.loop != null) ? true : false;
        GLib.stdout.printf("U7ThreadLoop [%s]: Starting loop [%i]\n", this.get_name(), (int)loop_exists);
    

    }

    private void recordThreadID() {
        
        this.setExtras(new U7ObjectExtras());

        main_lock.lock();
        uint64 next_id = thread_creation_count++;
        u7_tls_set_thread_uint64_id(next_id);
        this.setThreadID(next_id);
        U7NotificationCenter.registerThreadDispatcher(this);
        main_lock.unlock();

        //GLib.stdout.printf("U7ThreadLoop [%s]: ID: %" + uint64.FORMAT + "\n", this.get_name(), next_id);

    }

    private static void* thread_func(void* user_data) {
        U7ThreadLoop self = (U7ThreadLoop)user_data;

        //GLib.stdout.printf("thread_func: %p\n", user_data);

        self._private_threadEntrySetup();

        // Queue is already initialized in the constructor
        
        // Add message processing timeout source
        
        self.threadEntrySetup();
        //GLib.stdout.printf("U7ThreadLoop [%s]: Thread started\n", self.get_name());
        self.run();
        //GLib.stdout.printf("U7ThreadLoop [%s]: Loop stopped\n", self.get_name());
        self.context.pop_thread_default();

        return null;
    }

    public void start() {
        if (current_thread != null) {
            return;
        }

        try {
            new Thread<void*>.try(this.get_name(), () => {
                return thread_func(this);
            });
        } catch (GLib.Error e) {
            GLib.stdout.printf("Failed to start thread '%s': %s\n", this.get_name(), e.message);
            current_thread = null;
        }
    }

    public override string to_string() {
        return @"U7ThreadLoop [$(this.get_name())] (id: $(this.uuid()))";
    }
}

public class U7KeyboardInputMonitor : U7ThreadLoop {
    public U7KeyboardInputMonitor(string name) {
        base(name);
    }
    

    public override void threadEntrySetup() {
    
        GLib.stdout.printf("U7KeyboardInputMonitor [%s]: threadEntrySetup\n", this.get_name());

    }

    public override void run() {
        GLib.stdout.printf("U7KeyboardInputMonitor [%s]: Starting input monitor\n", this.get_name());
        GLib.stdout.flush();
        int sleep_count = 0;
        while (true) {
            char buffer[1024];
            ssize_t bytes = Posix.read(0, buffer, buffer.length);

            U7Dictionary message = this.try_pop();
            if (message != null)
                this.incrementMessageCount();

            if (bytes > 0) {

                GLib.stdout.printf("bytes %i|last 0x%02x|equal %i\n", (int)bytes, buffer[bytes - 1], (int)(buffer[bytes - 1] == 0x0a));

                if (buffer[bytes] == 0x0a)
                    bytes--;
                if (bytes > 0) {
                    buffer[bytes - 1] = 0;
                    string input = (string)buffer[0:bytes];
                    U7Dictionary info = U7Dictionary.with_pairs("input", new U7String(input), null);
                    U7NotificationCenter cntr = U7NotificationCenter.default();
                    if (cntr != null) {
                        if (input == "asdf") 
                            cntr.publish("keyboard_input_asdf", info);
                        else 
                            cntr.publish("keyboard_input", info);

                    }
    
    
                }
                
                GLib.stdout.flush();
            } else if (bytes == 0) {
                GLib.stdout.printf("U7KeyboardInputMonitor [%s]: EOF detected\n", this.get_name());
                break;
            } else {
                if (Posix.errno == Posix.EAGAIN || Posix.errno == Posix.EWOULDBLOCK) {
                    Thread.usleep(100000); // 100ms delay for non-blocking stdin
                    sleep_count++;
                    continue;
                } else {
                    GLib.stderr.printf("U7KeyboardInputMonitor [%s]: Read error: %s\n", 
                                       this.get_name(), Posix.strerror(Posix.errno));
                    break;
                }
            }
        }
    }

    public override string to_string() {
        return @"U7KeyboardInputMonitor (thread: $(this.get_name()))";
    }
}



public class U7ThreadSubscriber : U7ThreadLoop {

    private static U7ThreadSubscriber test_subscriber;
    public U7ThreadSubscriber(string name) {
        base(name);


    }

    public override void threadEntrySetup() {

        base.threadEntrySetup();

        subscribe("keyboard_output_request", (self, arg) => {
            string input = U7Utility.getStringFromDictionaryForKey(arg, "input");
            GLib.stdout.printf("U7ThreadSubscriber|thread_id %" + uint64.FORMAT + "|keyboard_output_request: %s\n", self.getThreadID(), input);
        });
        subscribe("keyboard_input", (self, arg) => {
            string input = U7Utility.getStringFromDictionaryForKey(arg, "input");
            GLib.stdout.printf("U7ThreadSubscriber|thread_id %" + uint64.FORMAT + "|keyboard_input: %s\n", self.getThreadID(), input);
        });


    }

    public override string to_string() {
        return @"U7ThreadSubscriber (thread: $(this.get_name()))";
    }

    public static void test() {
        test_subscriber = new U7ThreadSubscriber("U7ThreadSubscriber");        
        test_subscriber.start();
        //GLib.stdout.printf("U7ThreadSubscriber init() [%s]\n", test_subscriber.to_string());
    }
}
