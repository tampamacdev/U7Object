public class U7ObjectExtras : Object {

    public uint64 thread_id;
    public GLib.GenericArray<U7Object> observers;
    public GLib.GenericArray<string> subscriptions;

}



public class U7Object : Object {


    private static int instance_count = 0;
    private static uint64 total_alloc_count = 0;

    private static GLib.Mutex count_mutex = GLib.Mutex();
    private static Gee.HashMap<string, int> class_instance_tracker = new Gee.HashMap<string, int>();

    private Gee.HashMap<string, DelegateWrapper> _method_table;
    private uint64 _object_uuid;
    private U7ObjectExtras extras;

    protected delegate void U7MethodHandler(U7Object self, U7PropertyList? arg);

    public virtual string get_name() {return "U7Object";}

    public void setExtras(U7ObjectExtras e) {
        extras = e;
    }

    public virtual void publishOnThread(string name, U7Dictionary *info) {

        //stdout.printf("U7Object[%"  + uint64.FORMAT +  "]|publishOnThread %s\n", this.getThreadID(), name);

    }


    public void publish(string name, U7Dictionary *info) {
        
        //stdout.printf("U7Object[%"  + uint64.FORMAT +  "]|publish %s\n", this.getThreadID(), name);
        this.publishOnThread(name, info);

    }

    public void addSubscription(string sub) {
        bool found = false;
        uint index = 0;  // Declare here
        int count_before = -1, count_after = -1;
        if (extras != null) {
            count_before = extras.subscriptions.length;
            found = extras.subscriptions.find(sub, out index);
            if (found == false)
                extras.subscriptions.add(sub);
            count_after = extras.subscriptions.length;

        }
       
        //stdout.printf("addSubscription|cnt %i -> %i|index %i|found %i\n", count_before, count_after, (int)index, (int)found);


    }
    public void removeSubscription(string sub) {
        
    }


    public void setThreadID(uint64 tid) {

        bool has_extras = false;
        bool has_observers = false;

        if (extras != null) {
            has_extras = true;
            extras.thread_id = tid;
            if (extras.observers == null) {
                extras.observers = new GLib.GenericArray<U7Object>();
                extras.subscriptions = new GLib.GenericArray<string>();
                has_observers = true;
            }
        }

        //stdout.printf("has_extras %i|obs %i|setThreadID: %"  + uint64.FORMAT +  "\n", has_extras, has_observers, tid);

    }

    public GLib.GenericArray<string>? getSubscriptions() {

        GLib.GenericArray<string> array = null;
        bool has_array = false;
        uint64 tid = 0;
        if (extras != null) {
            array = extras.subscriptions;
            tid = extras.thread_id;
            if (array != null)
                has_array = true;
            
        }

        //stdout.printf("getSubscriptions|has_array %i|thread_id %"  + uint64.FORMAT +  "\n", has_array, tid);


        return array;
    }

    public GLib.GenericArray<U7Object>? getObservers() {

        GLib.GenericArray<U7Object> array = null;
        bool has_array = false;
        uint64 tid = 0;
        if (extras != null) {
            array = extras.observers;
            tid = extras.thread_id;
            if (array != null)
                has_array = true;
            
        }

        //stdout.printf("getObservers|has_array %i|thread_id %"  + uint64.FORMAT +  "\n", has_array, tid);


        return array;
    }
    
    public uint64 getThreadID() {
        if (extras != null)
            return extras.thread_id;
        return 0;
    }

    private class DelegateWrapper {
        private unowned U7MethodHandler handler;

        public DelegateWrapper(U7MethodHandler h) {
            this.handler = h;
        }

        public void invoke(U7Object self, U7PropertyList? arg) {
            handler(self, arg);
        }
    }

    public void subscribe(string method_name, U7MethodHandler handler) {

#if INCLUDE_C_BRIDGE_CODE
        U7MainEventLoop.subscribe_this(method_name, this);
#endif

        _method_table[method_name] = new DelegateWrapper(handler);
    }

    public virtual bool invoke_method(string method_name, U7PropertyList? arg, bool log) {
        bool success = false;
        if (method_name == null) {
            if (log)
                stdout.printf("%s.invoke_method: Null method name", this.get_name());
            return false;
        }
        if (_method_table.has_key(method_name)) {

            _method_table[method_name].invoke(this, arg);
            success = true;

            if (log)
                stdout.printf("%s.invoke_method: did invoke for method: '%s'", this.get_name(), method_name);

        } else {
            
            if (log)
                stdout.printf("%s.invoke_method: No implementation for '%s'", this.get_name(), method_name);
        }
        return success;
    }

    public void perform(string method_name, U7PropertyList? arg = null) {
        invoke_method(method_name, arg, false);
    }

    public static void init() {
        stdout.printf("Initializing U7Object API...\n");
    }

    public uint64 uuid() {
        return _object_uuid;
    }
    construct {

        _method_table = new Gee.HashMap<string, DelegateWrapper>();

        count_mutex.lock();
        instance_count++;
        _object_uuid = total_alloc_count++;

#if USE_OBJECT_TRACKING
        string class_name = this.get_type().name();
        int current_count = class_instance_tracker.has_key(class_name) 
            ? class_instance_tracker.get(class_name) 
            : 0;  // Default to 0 if key not found
        class_instance_tracker.set(class_name, current_count + 1);

        stdout.printf("Allocated %s, total count: %d, %s count: %d uuid: %"  + uint64.FORMAT +  "\n", 
                      class_name, instance_count, class_name, class_instance_tracker[class_name], _object_uuid);
#endif
        count_mutex.unlock();


    }

    public U7Object() {
    }

    ~U7Object() {
        instance_count--;
#if USE_OBJECT_TRACKING
        count_mutex.lock();
        string class_name = this.get_type().name();
        int current_count = class_instance_tracker.has_key(class_name) 
            ? class_instance_tracker.get(class_name) 
            : 0;  // Default to 0 if key not found
        class_instance_tracker.set(class_name, current_count - 1);
        stdout.printf("Deallocated %s, total count: %d, %s count: %d\n", 
                      class_name, instance_count, class_name, class_instance_tracker[class_name]);
        count_mutex.unlock();
#endif
    }

    public virtual string to_string() {
        return @"$(get_type().name()) (instance count: $(get_instance_count()))";
    }


    public static int get_instance_count() {
        return instance_count;
    }

    public static int get_class_instance_count(string class_name) {

#if USE_OBJECT_TRACKING
        count_mutex.lock();
        int count = class_instance_tracker.has_key(class_name) ? class_instance_tracker.get(class_name) : 0;
        count_mutex.unlock();
        return count;
#else
        return -1;  // Tracking disabled
#endif
    }

    public string get_class_name() {
        return this.get_type().name();
    }

    public static string get_all_class_instance_counts_report() {
        count_mutex.lock();
        var builder = new StringBuilder();
        builder.append("Class Instance Counts Report:\n");
#if USE_OBJECT_TRACKING
        foreach (var entry in class_instance_tracker.entries) {
            builder.append_printf("  %s: %d\n", entry.key, entry.value);
        }
#else
        builder.append("  Object tracking is disabled (-D USE_OBJECT_TRACKING not set)\n");
#endif
        builder.append_printf("Total instances(%p): %d\n", class_instance_tracker, instance_count);
        count_mutex.unlock();
        return builder.str;
    }
}

