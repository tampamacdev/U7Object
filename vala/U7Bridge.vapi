[CCode (cheader_filename = "u7_bridge.h")]
public GLib.Object u7_process_g_object(GLib.Object obj);

[CCode (cheader_filename = "u7_bridge.h")]
public int u7_process_int(int i);

[CCode (cheader_filename = "u7_bridge.h")]
public double u7_process_double(double d);

[CCode (cheader_filename = "u7_bridge.h")]
public string u7_process_c_string(string str);

[CCode (cheader_filename = "u7_bridge.h")]
public U7String u7_process_u7_string(U7String string);

[CCode (cheader_filename = "u7_bridge.h")]
public bool u7_process_bool(bool yn);

[CCode (cheader_filename = "u7_bridge.h")]
public void u7_tls_set_thread_uint64_id(uint64 value);

[CCode (cheader_filename = "u7_bridge.h")]
public uint64 u7_tls_get_thread_uint64_id();


[CCode (cheader_filename = "mongoose_vala_bridge.h")]
public void start_websocket_server(int port);

[CCode (cheader_filename = "mongoose_vala_bridge.h")]
public void stop_websocket_server();

