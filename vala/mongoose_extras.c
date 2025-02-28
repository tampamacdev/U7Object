#include "mongoose_extras.h"

#include "mongoose.h"

const char *mg_event_to_string(int event) {
    switch (event) {
        case MG_EV_ERROR: return "MG_EV_ERROR";
        case MG_EV_OPEN: return "MG_EV_OPEN";
        case MG_EV_POLL: return "MG_EV_POLL";
        case MG_EV_HTTP_MSG: return "MG_EV_HTTP_MSG";
        case MG_EV_CLOSE: return "MG_EV_CLOSE";
        case MG_EV_HTTP_CHUNK: return "MG_EV_HTTP_CHUNK";
        case MG_EV_WS_OPEN: return "MG_EV_WS_OPEN";
        case MG_EV_WS_MSG: return "MG_EV_WS_MSG";
        case MG_EV_WS_CTL: return "MG_EV_WS_CTL";
        case MG_EV_MQTT_CMD: return "MG_EV_MQTT_CMD";
        case MG_EV_MQTT_MSG: return "MG_EV_MQTT_MSG";
        case MG_EV_MQTT_OPEN: return "MG_EV_MQTT_OPEN";
        case MG_EV_CONNECT: return "MG_EV_CONNECT";
        case MG_EV_ACCEPT: return "MG_EV_ACCEPT";
        case MG_EV_RESOLVE: return "MG_EV_RESOLVE";
        default: return "UNKNOWN_EVENT";
    }
}
