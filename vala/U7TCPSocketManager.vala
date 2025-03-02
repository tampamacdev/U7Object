using GLib;

public async void worker_func (SocketConnection connection, Source source, Cancellable cancellable) {
	try {
		DataInputStream istream = new DataInputStream (connection.input_stream);
		DataOutputStream ostream = new DataOutputStream (connection.output_stream);

		// Get the received message:
		string message = yield istream.read_line_async (Priority.DEFAULT, cancellable);
		message._strip ();
		print ("Received: %s\n", message);

		// Response:
		ostream.put_string (message, cancellable);
		ostream.put_byte ('\n', cancellable);

		if (message == "shutdown") {
			cancellable.cancel ();
		}
	} catch (Error e) {
		print ("Error: %s\n", e.message);
	}
}


public class U7SocketConnection : U7Object {

    private GLib.SocketConnection connection;
    Object source_object;
    private GLib.DataInputStream data_input;
    //private GLib.Source? input_source; // Store source to keep it alive
    private int fd = -1;

    public U7SocketConnection(GLib.SocketConnection conn, Object? obj) {
        base();
        source_object = obj;
        connection = conn;

        data_input = new GLib.DataInputStream(connection.input_stream);

        if (data_input != null) {

            if (data_input.base_stream is GLib.FileInputStream) {

                //var file_input = data_input.base_stream as GLib.FileInputStream;
    
            }

        }
        GLib.stdout.printf("U7SocketConnection|fd %i\n", fd);
    
    }

}

public class U7TCPSocketManager : U7ThreadLoop {
    private GLib.SocketService? service = null;
    private uint16 port;
    private bool running = false;
    private AsyncQueue<U7SocketConnection> connectionQueue;

    public U7TCPSocketManager(string name, uint16 listen_port) {
        base(name);
        this.port = listen_port;
        this.connectionQueue = new AsyncQueue<U7SocketConnection>();

        GLib.stdout.printf("U7TCPSocketManager[%s]: init: %i\n", name, port);

    }
    
    private void check_queue() {

        GLib.stdout.printf("U7TCPSocketManager [%s:%" + uint64.FORMAT +  "]:threadEntrySetup() check_queueu\n", this.get_name(), U7ThreadLoop.getCurrentThreadID());

    }


    public override void threadEntrySetup() {
        base.threadEntrySetup();
        
        try {
            // Create TCP socket service

            /*
            Need open source community help here to move on_incoming_connection() callback to the U7ThreadLoop detached thread. Currently on_incoming_connection() is being called on the main thread.
            */

            service = new GLib.SocketService();

            // Bind to port (any interface)
            service.add_inet_port(port, null);
            
            // Add incoming connection handler
            service.incoming.connect((service, connection, source_object) => {

                U7SocketConnection *conn = new U7SocketConnection(connection, source_object);
                connectionQueue.push(conn);
                GLib.Idle.add(() => {
                    this.check_queue();
                    return false; // Keep the idle source active
                });
    
                return true;
            });


            GLib.stdout.printf("U7TCPSocketManager[%s]|threadEntrySetup\n", this.get_name());
            GLib.stdout.printf("U7TCPSocketManager [%s:%" + uint64.FORMAT +  "]:threadEntrySetup() Listening on port: %u\n", this.get_name(), U7ThreadLoop.getCurrentThreadID(), port);

            
        } catch (Error e) {
            GLib.stderr.printf("U7TCPSocketManager [%s]: Setup error: %s\n",
                this.get_name(), e.message);
        }
    }
    
    private bool on_incoming_connection(GLib.SocketConnection connection, Object? source_object) {
        try {
            // Get client info
            GLib.InetSocketAddress remote_address = (GLib.InetSocketAddress)connection.get_remote_address();
            string client_ip = remote_address.get_address().to_string();
            uint16 client_port = (uint16)remote_address.get_port();
        
            GLib.stdout.printf("U7TCPSocketManager [%s:%" + uint64.FORMAT +  "]: New connection from %s:%u\n",
                this.get_name(), U7ThreadLoop.getCurrentThreadID(), client_ip, client_port);
            

            // Handle client connection in a separate thread
            handle_client(connection, client_ip, client_port);
            
            return true; // Keep listening for new connections
        } catch (Error e) {
            GLib.stderr.printf("U7TCPSocketManager [%s]: Error handling connection: %s\n",
                this.get_name(), e.message);
            return true; // Keep the listener active even if one connection fails
        }
    }
    
    private void handle_client(GLib.SocketConnection connection, string client_ip, uint16 client_port) {
        try {
            // Get input and output streams
            GLib.InputStream input = connection.input_stream;
            //GLib.OutputStream output = connection.output_stream;
            
            // Read data in a loop
            GLib.DataInputStream data_input = new GLib.DataInputStream(input);
            string? line;
            
            while ((line = data_input.read_line()) != null) {
                // Publish received data
                var data = U7Dictionary.with_pairs(
                    "client_ip", new U7String(client_ip),
                    "client_port", new U7Number.from_int(client_port),
                    "message", new U7String(line),
                    null
                );
                U7NotificationCenter cntr = U7NotificationCenter.default();
                cntr.publish("tcp_data_received", data);
                 
                GLib.stdout.printf("U7TCPSocketManager [%s:%" + uint64.FORMAT +  "]: Received from client_ip <%s>|port %u|line: %s\n",
                    this.get_name(), U7ThreadLoop.getCurrentThreadID(), client_ip, client_port, line);
            }
            
            GLib.stdout.printf("U7TCPSocketManager [%s]: Client %s:%u disconnected\n",
                this.get_name(), client_ip, client_port);
                
        } catch (Error e) {
            GLib.stderr.printf("U7TCPSocketManager [%s]: Error with client %s:%u: %s\n",
                this.get_name(), client_ip, client_port, e.message);
        } finally {
            try {
                connection.close();
            } catch (Error e) {
                GLib.stderr.printf("U7TCPSocketManager [%s]: Error closing connection: %s\n",
                    this.get_name(), e.message);
            }
        }
    }
    
    public override void run() {
        GLib.stdout.printf("U7TCPSocketManager [%s]: Starting TCP listener\n", 
            this.get_name());
        
        if (service == null) {
            GLib.stderr.printf("U7TCPSocketManager [%s]: Cannot run - service not initialized\n",
                this.get_name());
            return;
        }
        
        // Start the service
        service.start();
        running = true;
        
        base.run(); // Runs the MainLoop to process IO events
    }
    
    ~U7TCPSocketManager() {
        if (service != null && running) {
            service.stop();
        }
    }
    
    public override string to_string() {
        return @"U7TCPSocketManager [$(this.get_name())] (port: $port)";
    }
    
    // Static test method called from main
    public static void test() {
        var tcp_manager = new U7TCPSocketManager("TestTCPManager", 9124);
        tcp_manager.start();
    }
}