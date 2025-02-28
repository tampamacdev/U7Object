#include "u7mainloop.h"

struct _U7MainLoop {
    GObject parent_instance;
    GMainLoop *main_loop;
    void (*callback)(char *str, int len);
};


void (*global_keybaord_input_callback)(char *str, int len) = NULL;

gboolean keyboard_input(GIOChannel *source, GIOCondition condition, gpointer data) {
    gchar *str = NULL;
    gsize len = 0;

    if (g_io_channel_read_line(source, &str, &len, NULL, NULL) == G_IO_STATUS_NORMAL) {

        if (global_keybaord_input_callback != NULL) {
            // Call the user-provided callback function
            global_keybaord_input_callback(str, len);
        } else 
            g_print("You entered: %s", str);

        if (g_strcmp0(str, "exit\n") == 0) {
            g_print("Exiting main loop.\n");
            g_main_loop_quit((GMainLoop *)data);
        }
        g_free(str);
    }

    return TRUE; // Return TRUE to keep the callback active
}



void u7_mainloop_start(U7MainLoop *loop) {

    global_keybaord_input_callback = loop->callback;

    GIOChannel *channel = g_io_channel_unix_new(fileno(stdin));

    g_io_add_watch(channel, G_IO_IN, keyboard_input, loop->main_loop);

    g_print("Enter text and press Enter (type 'exit' to quit):\n");
    g_main_loop_run(loop->main_loop);

    g_io_channel_unref(channel);
    g_main_loop_unref(loop->main_loop);

}





struct _U7MainLoopClass {
    GObjectClass parent_class;
};

G_DEFINE_TYPE(U7MainLoop, u7_mainloop, G_TYPE_OBJECT)

static void u7_mainloop_class_init(U7MainLoopClass *klass) {
    // Class initialization logic, if needed
}

static void u7_mainloop_init(U7MainLoop *self) {
    self->main_loop = g_main_loop_new(NULL, FALSE);
    self->callback = NULL;
}

U7MainLoop* u7_mainloop_new(void (*callback)(char *str, int len)) {
    U7MainLoop *self = g_object_new(U7_TYPE_MAINLOOP, NULL);
    self->callback = callback;
    return self;
}
