
    

public class U7WebSocketManager : U7ThreadLoop {

    private static U7WebSocketManager test_subscriber;
    public U7WebSocketManager(string name) {
        base(name);

    }

    public override void threadEntrySetup() {

        base.threadEntrySetup();
        subscribe("keyboard_input_socket", (self, arg) => {

            string input = U7Utility.getStringFromDictionaryForKey(arg, "input");
            if (input != null)
                GLib.stdout.printf("U7WebSocketManager|thread_id %" + uint64.FORMAT + "|keyboard_input_socket: %s\n", self.getThreadID(), input);

        });

        subscribe("keyboard_input", (self, arg) => {

            string input = U7Utility.getStringFromDictionaryForKey(arg, "input");
            if (input != null)
                GLib.stdout.printf("U7WebSocketManager|thread_id %" + uint64.FORMAT + "|keyboard_input: %s\n", self.getThreadID(), input);

        });


        start_websocket_server(9204);
    }

    public override string to_string() {
        return @"U7WebSocketManager (thread: $(this.get_name()))";
    }

    public static void test_json() {

        U7Dictionary test = U7PropertyList.test_dictionary();
        string json = test.to_json_string();
        GLib.stdout.printf("U7WebSocketManager init() [%s]\n", json);

        try {

            U7PropertyList info = U7PropertyList.parse_json_string(json);

            U7Dictionary dict = info as U7Dictionary;
            if (dict != null) {
                string info_json = info.to_json_string();
    
                GLib.stdout.printf("U7WebSocketManager info_json() [%s]\n", info_json);
    
            } else {
                GLib.stdout.printf("U7WebSocketManager unable to parse json()\n");
    
            }
    
        } catch (U7Error e) {
            if (e is U7Error.INVALID_FORMAT) {
                stderr.printf("Invalid format error: %s\n", e.message);
            } else {
                stderr.printf("Other U7 error: %s\n", e.message);
            }
        }

    }

    public static void test() {



        test_subscriber = new U7WebSocketManager("U7WebSocketManager");        
        test_subscriber.start();
        //GLib.stdout.printf("U7ThreadSubscriber init() [%s]\n", test_subscriber.to_string());


    }

}

