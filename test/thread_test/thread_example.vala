using GLib;

class ThreadExample : Object {
    private Thread<void *> worker_thread;
    private MainLoop main_loop;
    private ThreadSafeQueue<string> message_queue;

    public ThreadExample() {
        message_queue = new ThreadSafeQueue<string>();
    }

    // Worker thread with its own MainLoop
    private void *worker_thread_func() {
        // Create a new MainContext for this thread
        MainContext worker_context = new MainContext();
        worker_context.push_thread_default();

        // Create and run a MainLoop for this thread
        MainLoop worker_loop = new MainLoop(worker_context, false);
        
        // Set up a source to check the queue
        Timeout.add(100, () => {
            string? message = message_queue.try_pop();
            if (message != null) {
                stdout.printf("Worker thread received: %s\n", message);
            }
            return Source.CONTINUE;
        });

        stdout.printf("Worker thread starting its MainLoop\n");
        worker_loop.run();

        worker_context.pop_thread_default();
        return null;
    }

    // Method to send message from main thread to worker thread
    public void send_message(string message) {
        message_queue.push(message);
    }

    public void start() {
        // Create the worker thread
        try {
            worker_thread = new Thread<void *>("worker-thread", worker_thread_func);
        } catch (Error e) {
            stderr.printf("Error creating thread: %s\n", e.message);
            return;
        }

        // Main thread's MainLoop
        main_loop = new MainLoop(null, false);

        // Example: Send messages periodically
        Timeout.add_seconds(2, () => {
            send_message("Hello from main thread at " + new DateTime.now_local().to_string());
            return Source.CONTINUE;
        });

        main_loop.run();
    }

    public static int main(string[] args) {
        var app = new ThreadExample();
        app.start();
        return 0;
    }
}

// Simple thread-safe queue implementation
class ThreadSafeQueue<T> : Object {
    private Queue<T> queue;
    private Mutex mutex;
    private Cond cond;

    public ThreadSafeQueue() {
        queue = new Queue<T>();
        mutex = Mutex();
        cond = Cond();
    }

    public void push(T item) {
        mutex.lock();
        queue.push_tail(item);
        cond.signal();
        mutex.unlock();
    }

    public T? try_pop() {
        mutex.lock();
        T? item = queue.pop_head();
        mutex.unlock();
        return item;
    }
}