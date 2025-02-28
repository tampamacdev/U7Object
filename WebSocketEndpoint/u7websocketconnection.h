#pragma once
#include "u7glib.h"

G_BEGIN_DECLS

#define U7_TYPE_WEBSOCKETCONNECTION (u7_websocketconnection_get_type())

#define U7IsWebSocketConnection(n) g_type_check_instance_is_a((GTypeInstance*)n, U7_TYPE_WEBSOCKETCONNECTION)

G_DECLARE_FINAL_TYPE(U7WebSocketConnection, u7_websocketconnection, U7, WEBSOCKETCONNECTION, U7Object)

extern U7WebSocketConnection *u7_websocketconnection_new(void *owner);
extern void u7client_event_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data);

G_END_DECLS
