#include "websocketendpoint.h"


// Example callback function
void keyboard_input_callback(char *str, int len) {
    g_print("Callback received: %sLength: %d\n", str, len);
}


void test(char *string, int len) {


    char *input = "abcdefghijklmnopqrstuvwxyz1234567890";
    int encrypted_data_len = 0, decrypted_data_len = 0, input_len = strlen(input);
    char *encrypted_data = u7_encrypt(input, input_len, &encrypted_data_len, "mypassword");
    char *decrypted_data = u7_decrypt(encrypted_data, encrypted_data_len, &decrypted_data_len, "mypassword");

    u7loghex("input", input, input_len);

    u7loghex("encrypted_data", encrypted_data, encrypted_data_len);
    u7loghex("decrypted_data", decrypted_data, decrypted_data_len);

    if (input_len == decrypted_data_len) {

        int check = memcmp(input, decrypted_data, input_len);

        printf("check %i\n", check);

    }

    if (encrypted_data)
        free(encrypted_data);
    if (decrypted_data)
        free(decrypted_data);

    char buf[256];
    for (int i = 0; i < 256; i++) buf[i] = i;


    u7loghex("test", buf, 256);


}

int main(int argc, char *argv[]) {

    //test("hello", 0); return -1;

    u7glib_init(argc, argv, 
                        "-port", "9201",
                        "-password", "default_password_FFs83h41@",
                        "-remote_url", "127.0.0.1:9301", NULL);


    printf("\
////////////////////////////////////////////////////////////////////\n\
////////////////////////////////////////////////////////////////////\n\
/////\n\
/////           WebSocketEndpoint\n\
/////\n\
/////           port %s|remote_ip %s\n\
/////\n\
////////////////////////////////////////////////////////////////////\n\
////////////////////////////////////////////////////////////////////\n", get_global_info_value("port"), get_global_info_value("remote_ip"));



    U7MainLoop *loop = u7_mainloop_new(keyboard_input_callback);

    WebSocketManager *ws = ws7_object_new(loop, get_global_info_value_int("port"));

    printf("ws: %p loop: %p\n", ws, loop);

    u7_array_test();
    //u7_jsonobject_test();
    //u7_string_test();

    u7_mainloop_start(loop);



    return 0;

}