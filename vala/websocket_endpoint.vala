
public class AppDelegate : U7Object {

    construct {

        subscribe("keyboard_input_asdf", (self, arg) => {
            
            string input = U7Utility.getStringFromDictionaryForKey(arg, "input");
            if (input != null) 
                GLib.stdout.printf("keyboard_input: %s\n", input);
            else 
                GLib.stdout.printf("no input string: %s\n", input);


        });


    }
}


int main(string[] args) {

    
#if INCLUDE_C_BRIDGE_CODE

    stdout.printf("Starting WebSocket server from Vala...\n");
    U7Bridge.init();

    //return test();

    U7ThreadSubscriber.test();
    U7WebSocketManager.test();
    U7TCPSocketManager.test();

    AppDelegate *appDel = new AppDelegate();
    
    if (appDel != null) 
        stdout.printf("AppDelegate\n");

    var input_monitor = new U7KeyboardInputMonitor("U7KeyboardInputMonitor");
    input_monitor.start();
    stdout.printf("include_c_bridge_code=true\n");

    
    U7ThreadLoop.startMainEventLoop();



#else
    
    stdout.printf("include_c_bridge_code=false\n");

#endif


    return 0;
}