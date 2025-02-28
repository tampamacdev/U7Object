
public class U7Bridge : U7Object {

    public U7Bridge() {

    }

    public new static void init() {
        stdout.printf("Initializing U7Bridge API...\n");
        U7ThreadLoop.init();

        // Add other subclasses as needed
    }


    public static void test() {

        string str = u7_process_c_string("test string");
        
        stdout.printf("U7Bridge.test()|%s\n", str);

        U7String u7str = new U7String("new U7String");
        U7String returnU7String = u7_process_u7_string(u7str);

        stdout.printf("returnU7String|%s\n", returnU7String.to_string());

        //U7Dictionary info = U7PropertyList.test_dictionary();
        //string json = info.to_json_string();
        //stdout.printf("U7Dictionary.test_dictionary()|%s\n", json);


    }

}
