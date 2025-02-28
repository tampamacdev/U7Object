#pragma once


#include "u7glib.h"

typedef struct ws_connection {
    struct mg_connection *conn;         // Pointer to the WebSocket connection
    struct ws_connection *next;         // Pointer to the next connection in the list
} ws_connection_t;

typedef struct _WebSocketManager {

    GObject parent_instance;
    GThread *thread;  
    gboolean has_valid_thread;
    GMutex lock;
    U7MainLoop *loop;
    char listen_url[128];
    char remote_url[128];
    struct mg_mgr mongoose_manager;

    ws_connection_t *ws_connections;
    // Add private instance fields here
} WebSocketManager;

// Constructor
WebSocketManager *ws7_object_new(U7MainLoop *loop, int port);
extern U7WebSocketConnection *ws7_add_connection(WebSocketManager *mngr, char *url);
extern void ws7_test(void);

