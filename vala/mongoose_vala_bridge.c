// mongoose_vala_bridge.c
#include "mongoose.h"
#include "shared.h"
#include "u7_api.h"
#include "u7_notification_center.h"

U7NotificationCenter *notification_center = NULL;


static struct mg_mgr mgr;
static int is_running = 0;

gboolean u7_cstrings_are_equal(const char *str1, int str1_len, const char *trimmed_str2, int str2_len) {
    gboolean are_equal = false;
    int leading_gap = 0, trailing_gap = 0;

    if (str1 && trimmed_str2) {
        if (str1_len >= str2_len) {
            char *result = g_ascii_strdown((gchar *)str1, str1_len);
            char *cmp_str = g_ascii_strdown((gchar *)trimmed_str2, str2_len);
            char *found = strstr(result, cmp_str);

            if (found) {
                leading_gap = found - result;
                trailing_gap = str1_len - leading_gap - str2_len;

                if ((leading_gap + str2_len + trailing_gap) == str1_len) {
                    for (int i = 0; i < leading_gap; i++) {
                        if (!isspace((unsigned char)str1[i])) {
                            g_free(result);
                            g_free(cmp_str);
                            return false;
                        }
                    }

                    for (int i = str2_len + leading_gap; i < str1_len; i++) {
                        if (!isspace((unsigned char)str1[i])) {
                            g_free(result);
                            g_free(cmp_str);
                            return false;
                        }
                    }

                    are_equal = true;
                }
            }
            g_free(result);
            g_free(cmp_str);
        }
    }

    return are_equal;
}


static void handle_web_socket_message(char *message) {

    GError *error = NULL;
    U7PropertyList *info = NULL;

    // Call the method with error parameter
    info = u7_property_list_parse_json_string(message, &error);

    // Check if an error occurred
    if (error != NULL) {
        // Handle the error
        if (g_error_matches(error, u7_error_quark(), U7_ERROR_INVALID_FORMAT)) {
            g_printerr("Invalid format error: %s\n", error->message);
        } else {
            g_printerr("Unknown error: %s\n", error->message);
        }
        
        // Free the error
        g_error_free(error);
        return;
    } 

    // If we get here, info should be valid
    if (info != NULL) {

        gchar *json = u7_property_list_to_json_string(info);
        if (json) {
            printf("handle_web_socket_message received valid json: %s\n", json);
            g_free(json);
        }

        gchar *name = u7_utility_getStringFromDictionaryForKey(info, "name");
        if (name) {

            printf("dispatching web socket message named <%s>\n", name);
            u7_notification_center_publish(notification_center, name, info);
            g_free(name);
        }
        // Use info here
        // Remember to unref it when done since it's a GObject
        g_object_unref(info);
    }
}



static void handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {

    struct mg_http_message *hm = (struct mg_http_message *)ev_data;

    if (ev == MG_EV_OPEN) {
        printf("Connection opened\n");
    } else if (ev == MG_EV_HTTP_MSG) {

        const struct mg_str *upgrade = mg_http_get_header(hm, "Upgrade");
        const struct mg_str *conn = mg_http_get_header(hm, "Connection");
        printf("HTTP message %s\n", hm->uri);

        if (u7_cstrings_are_equal((const char *)upgrade->ptr, upgrade->len, "websocket", 9) && 
            u7_cstrings_are_equal((const char *)conn->ptr, conn->len, "upgrade", 7))
        {
            printf("WebSocket upgrade requested.\n");
            mg_ws_upgrade(c, hm, NULL);
        } else {

           //handle_request(c, hm, NULL);


        }



    } else if (ev == MG_EV_WS_OPEN) {
        printf("WebSocket connection established\n");
        mg_ws_send(c, "Hello WebSocket!", 16, WEBSOCKET_OP_TEXT);
    } else if (ev == MG_EV_WS_MSG) {

        struct mg_ws_message *wm = (struct mg_ws_message *)ev_data;

        gchar* null_terminated = g_strndup(wm->data.ptr, wm->data.len);
        if (null_terminated) {
            handle_web_socket_message(null_terminated);
            g_free(null_terminated);
        }
        printf("WebSocket message: %.*s\n", (int)wm->data.len, wm->data.ptr);
        mg_ws_send(c, wm->data.ptr, wm->data.len, WEBSOCKET_OP_TEXT);

    } else if (ev == MG_EV_CLOSE) {
        printf("Connection closed\n");
    }
}

void start_websocket_server(int port) {


    if (is_running) return;

    mg_mgr_init(&mgr);
    char address[32];
    snprintf(address, sizeof(address), "http://0.0.0.0:%d", port);

    struct mg_connection *c = mg_http_listen(&mgr, address, handler, NULL);
    if (c == NULL) {
        printf("Failed to start server on port %d\n", port);
        mg_mgr_free(&mgr);
        return;
    }

    notification_center = u7_notification_center_default();

    is_running = 1;
    printf("websocket server started on port %d|notification_center %p\n", port, notification_center);

    while (is_running) {
        mg_mgr_poll(&mgr, 1000);
    }
}

void stop_websocket_server() {
    if (!is_running) return;
    is_running = 0;
    mg_mgr_free(&mgr);
    printf("Server stopped\n");
}