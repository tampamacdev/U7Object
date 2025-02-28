public class U7MainEventLoop : U7ThreadLoop {



    public U7MainEventLoop(string name) {
        base(name);
    }

    construct {

        GLib.stdout.printf("U7MainEventLoop construct\n");

        subscribe("keyboard_input", (self, arg) => {


            string input = U7Utility.getStringFromDictionaryForKey(arg, "input");
            if (input != null) 
                GLib.stdout.printf("U7MainEventLoop|thread_id %" + uint64.FORMAT + "|keyboard_input: %s\n", self.getThreadID(), input);

        });

        subscribe("keyboard_input_asdf", (self, arg) => {


            string input = U7Utility.getStringFromDictionaryForKey(arg, "input");
            if (input != null) 
                GLib.stdout.printf("U7MainEventLoop|thread_id %" + uint64.FORMAT + "|keyboard_input_asdf: %s\n", self.getThreadID(), input);

        });


    }

#if INCLUDE_C_BRIDGE_CODE

    public static void subscribe_this(string name, U7Object observer) {

        U7NotificationCenter cntr = U7NotificationCenter.default();
        if (cntr != null) {
            cntr.subscribe(name, observer);
        }
        
    }

#endif

}