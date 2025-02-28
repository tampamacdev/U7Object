#include "u7websocketconnection.h"
#include "websocketendpoint.h"

struct _U7WebSocketConnection {
    U7Object parent_instance;
    WebSocketManager *owner;
};

struct _U7WebSocketConnectionClass {
    U7ObjectClass parent_class;
};

G_DEFINE_TYPE(U7WebSocketConnection, u7_websocketconnection, U7_TYPE_OBJECT)

static void u7_websocketconnection_dispose(GObject *object) {
    printf("u7_websocketconnection_dispose\n");

    G_OBJECT_CLASS(u7_websocketconnection_parent_class)->dispose(object);

}

static char *u7_websocketconnection_description(U7Object *obj) {
    if (U7IsWebSocketConnection(obj)) 
        return "u7_websocketconnection_description need to implement";
    return "u7_websocketconnection_description";
}

static void u7_websocketconnection_class_init(U7WebSocketConnectionClass *klass) {
    // Class initialization logic, if needed
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->dispose = u7_websocketconnection_dispose;

    U7ObjectClass *u7_object_class = U7_OBJECT_CLASS(klass);
    u7_object_class->description = u7_websocketconnection_description;

}

static void u7_websocketconnection_init(U7WebSocketConnection *self) {
    printf("u7_websocketconnection_init\n");
}

U7WebSocketConnection *u7_websocketconnection_new(void *owner) {
    U7WebSocketConnection *self = g_object_new(U7_TYPE_WEBSOCKETCONNECTION, NULL);
    return self;
}


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////
///////
///////           WebSocket client connection 
///////
///////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

void u7client_event_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {

    if (ev != MG_EV_POLL) {

        /*
            NOTE: event types determine what ev_data is
        */

        printf("client_event_handler|ev(%i) %s\n", ev, mg_event_to_string(ev));

    }
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        mg_http_reply(c, 200, "", "Hello, %.*s!\n", (int) hm->uri.len, hm->uri.ptr);
    } else if (ev == MG_EV_WS_OPEN) {
        printf("Connected to WebSocket server\n");
        mg_ws_send(c, "Hello Server!", strlen("Hello Server!"), WEBSOCKET_OP_TEXT);
    } else if (ev == MG_EV_WS_MSG) {
        struct mg_ws_message *wm = (struct mg_ws_message *) ev_data;
        printf("Received message: %.*s\n", (int) wm->data.len, wm->data.ptr);
    } else if (ev == MG_EV_CLOSE) {
        printf("Connection closed\n");
    } else if (ev == MG_EV_ERROR) {
        const char *error_message = (const char *) ev_data;
        printf("Connection error: %s\n", error_message);
    }
    (void) fn_data;
}
