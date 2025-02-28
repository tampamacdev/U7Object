#include "websocketendpoint.h"

typedef struct {

    char *buf;
    int len;

} WebSocketMessage;

typedef struct {

    double last_activity; // Timestamp of last activity (message or heartbeat)
    WebSocketMessage message;

} WebSocketConnectionInfo;

// Function to add a new WebSocket connection to the list
void add_ws_connection(struct mg_connection *c, struct ws_connection **ws_connections) {
  struct ws_connection *new_conn = (struct ws_connection *) malloc(sizeof(struct ws_connection));
  if (new_conn) {
    new_conn->conn = c;
    new_conn->next = *ws_connections;
    *ws_connections = new_conn;
  }
}

// Function to remove a WebSocket connection from the list
void remove_ws_connection(struct mg_connection *c, struct ws_connection **ws_connections) {
  struct ws_connection **current = ws_connections;

  while (*current) {
    if ((*current)->conn == c) {
      struct ws_connection *to_free = *current;
      *current = (*current)->next;  // Remove the connection from the list
      free(to_free);  // Free the allocated memory
      return;
    }
    current = &(*current)->next;
  }
}

static int connection_count(struct ws_connection **c) {
    struct ws_connection **current = c;
    int count = 0;
    while (*current) {
        current = &(*current)->next;
        count++;
    }
    return count;
}

static void send_heartbeat(double time, struct ws_connection **ws_connections) {

    struct ws_connection **current = ws_connections;
    char heartbeat_buf[128];
    char hms[32];
    char elapse_desc[32];

    int count = 0;
    char *stamp = NULL;
    while (*current) {

        struct ws_connection *wsc = *current;
        struct mg_connection *c = wsc->conn;

        WebSocketConnectionInfo *info = (WebSocketConnectionInfo *)c->user_data;
        if (info) {

            double elapse = time - info->last_activity;
            if (elapse >= 60.0) {

                if (stamp == NULL)
                    stamp = u7_timestamp_create();
                sprintf(heartbeat_buf, "heartbeat|time %s|elapse %s|%s", u7_hms(hms, time), u7_hms(elapse_desc, elapse), stamp);
                mg_ws_send(c, heartbeat_buf, strlen(heartbeat_buf), WEBSOCKET_OP_TEXT);
                printf("%s\n", heartbeat_buf);
                info->last_activity = time;
                count++;

            }

        }


        current = &(*current)->next;
    }

    if (stamp)
        free(stamp);

    //printf("count %i\n", count);

}

static void cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    
    WebSocketManager *websocket = fn_data;
    if (c == NULL) {

        printf("missing connection info: fn_data: %p\n", fn_data);

        return;
    }

    uint64_t key = c->id;

    struct mg_http_message *hm = (struct mg_http_message *) ev_data;


    if (ev != MG_EV_POLL) {

        /*
            NOTE: event types determine what ev_data is
        */

        //printf("callback|ev(%i) %s\n", ev, mg_event_to_string(ev));

    }

    if (ev == MG_EV_OPEN) {


    } else if (ev == MG_EV_HTTP_MSG) {
    
        const struct mg_str *upgrade = mg_http_get_header(hm, "Upgrade");
        const struct mg_str *conn = mg_http_get_header(hm, "Connection");


        if (u7_cstrings_are_equal((const char *)upgrade->ptr, upgrade->len, "websocket", 9) && 
            u7_cstrings_are_equal((const char *)conn->ptr, conn->len, "upgrade", 7))
        {
            printf("WebSocket upgrade requested.\n");
            mg_ws_upgrade(c, hm, NULL);
        } else {

           //handle_request(c, hm, NULL);


        }

    
    } else if (ev == MG_EV_HTTP_CHUNK) {


    } else if (ev == MG_EV_WS_OPEN) {

        void *user_data_before = c->user_data;
        WebSocketConnectionInfo *info = c->user_data = calloc(1, sizeof(WebSocketConnectionInfo));
        info->last_activity = -3600.0f;
        // WebSocket connection is established, add to the connection list
        void *ws_connections_before = websocket->ws_connections;
        add_ws_connection(c, &websocket->ws_connections);
        printf("WebSocket connection opened|active %i|user_data before %p after %p|conns %p-%p\n", connection_count(&websocket->ws_connections), user_data_before, c->user_data, ws_connections_before, websocket->ws_connections);

        
        //mg_ws_send(c, "Welcome to the WebSocket server!", 33, WEBSOCKET_OP_TEXT);

    } else if (ev == MG_EV_WS_MSG) {

        
        WebSocketConnectionInfo *info = (WebSocketConnectionInfo *)c->user_data;

        if (info) {

            struct mg_ws_message *wm = (struct mg_ws_message *)ev_data;

            info->message.len = wm->data.len;
            info->message.buf = (char *)malloc(info->message.len + 1);
            memcpy(info->message.buf, wm->data.ptr, info->message.len);
            info->message.buf[info->message.len] = 0;


            printf("messsage.buf %s\n", info->message.buf);

            mg_ws_send(c, info->message.buf, info->message.len, WEBSOCKET_OP_TEXT);

        }



    } else if (ev == MG_EV_CLOSE) {

        void *ws_connections_before = websocket->ws_connections;
        WebSocketConnectionInfo *info = (WebSocketConnectionInfo *)c->user_data;
        void *buf = NULL;
        if (info) {

            remove_ws_connection(c, &websocket->ws_connections);

            if ((buf = info->message.buf)) 
                free(info->message.buf);
            free(info);
            c->user_data = NULL;
        }

        printf("MG_EV_CLOSE|active %i|info %p|buf %p|conns %p-%p\n", connection_count(&websocket->ws_connections), info, buf, ws_connections_before, websocket->ws_connections);


    }
  
}


void *mongoose_polling_thread(void *user_info) {

    WebSocketManager *websocket = (WebSocketManager *)user_info;

    // g_mutex_lock g_mutex_unlock

    printf("mongoose_polling_thread() websocket: %p\n", websocket);
    printf("websocket->listen_url %s\n", websocket->listen_url);
    printf("websocket->remote_url %s\n", websocket->remote_url);

    struct mg_mgr *mgr = &websocket->mongoose_manager;
    mg_mgr_init(mgr);
    mg_log_set(MG_LL_DEBUG);  

    struct mg_connection *listen_connection = mg_http_listen(&websocket->mongoose_manager, websocket->listen_url, cb, websocket);

    printf("mg_http_listen()|listen_connection %p\n", listen_connection);

    int count = 0;
    double start = u7_time();
    if (listen_connection) {


        while (1) {
            
            double now = u7_time() - start;

            send_heartbeat(now, &websocket->ws_connections);
            //u7_check_response_queue();
            //u7_check_for_status_update();
            mg_mgr_poll(&websocket->mongoose_manager, 50);
        }


    } else {

        printf("unable to create connection\n");

    }
    return NULL;

}

WebSocketManager *ws7_object_new(U7MainLoop *loop, int port)
{
    WebSocketManager *ws = calloc(1, sizeof(WebSocketManager));

    if (ws) {

        sprintf(ws->listen_url, "http://0.0.0.0:%i", port);
        sprintf(ws->remote_url, "%s", get_global_info_value("remote_url"));

        printf("ws7_object_new()|listen_url %s\n", ws->listen_url);

        g_mutex_init(&ws->lock);

        ws->thread = g_thread_new("mongoose-poll", mongoose_polling_thread, ws);

        ws->has_valid_thread = (ws->thread != NULL);

        if (loop) {

            g_object_ref(loop);
            ws->loop = loop;

        } else {

            ws->loop = NULL;

        }

    }

    return ws;
}


U7WebSocketConnection *ws7_add_connection(WebSocketManager *mngr, char *url) {

    U7WebSocketConnection *c = NULL;


    return c;

}

void ws7_test(void) {


    printf("%s/////   ws7_test()\n%s", j7_log_divider, j7_log_divider);



}