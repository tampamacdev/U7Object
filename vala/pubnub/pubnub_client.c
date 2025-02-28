// endpoint.c
#include "pubnub_coreapi.h"
#include "pubnub_alloc.h"
#include 
#include 

int main() {
    pubnub_t* pb = pubnub_alloc();
    pubnub_init(pb, "pub-c-98f5d838-634f-4470-9373-d7587235d0fc", "sub-c-dcaa090d-090b-4055-88d9-41920427229f");
    pubnub_set_uuid(pb, "endpoint-1");
    pubnub_set_uuid_metadata(pb, "barracuda6", "{\"domain\":\"engaged-dodo-valid.ngrok-free.app\"}");
    pubnub_await(pb);
    pubnub_subscribe(pb, "endpoint-directory", NULL);
    pubnub_await(pb);
    printf("Endpoint registered\n");
    while (1) sleep(60); // Stay active
    pubnub_free(pb);
    return 0;
}
