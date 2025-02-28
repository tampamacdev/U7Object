#include "u7_bridge.h"
#include "u7_api.h"
#include <stdio.h>


// custom_tls.c
#include <stdint.h>
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

// TLS key for storing a single uint64 per thread
#ifdef _WIN32
static DWORD tls_index;
static CRITICAL_SECTION init_mutex;
static int initialized = 0;
#else
static pthread_key_t tls_key;
static pthread_mutex_t init_mutex = PTHREAD_MUTEX_INITIALIZER;
static int initialized = 0;
#endif

// Initialize the TLS system
static void tls_init() {
#ifdef _WIN32
    EnterCriticalSection(&init_mutex);
    if (!initialized) {
        tls_index = TlsAlloc();
        if (tls_index == TLS_OUT_OF_INDEXES) {
            fprintf(stderr, "Failed to allocate TLS index\n");
            exit(1);
        }
        initialized = 1;
    }
    LeaveCriticalSection(&init_mutex);
#else
    pthread_mutex_lock(&init_mutex);
    if (!initialized) {
        if (pthread_key_create(&tls_key, NULL) != 0) { // No destructor needed
            fprintf(stderr, "Failed to create TLS key\n");
            exit(1);
        }
        initialized = 1;
    }
    pthread_mutex_unlock(&init_mutex);
#endif
}

// Set the TLS uint64 value for the current thread
void u7_tls_set_thread_uint64_id(uint64_t value) {
    if (!initialized) {
#ifdef _WIN32
        InitializeCriticalSection(&init_mutex);
#endif
        tls_init();
    }

#ifdef _WIN32
    TlsSetValue(tls_index, (void*)(uintptr_t)value); // Cast uint64 to pointer
#else
    pthread_setspecific(tls_key, (void*)(uintptr_t)value); // Cast uint64 to pointer
#endif
}

// Get the TLS uint64 value for the current thread
uint64_t u7_tls_get_thread_uint64_id() {
    if (!initialized) {
#ifdef _WIN32
        InitializeCriticalSection(&init_mutex);
#endif
        tls_init();
    }

#ifdef _WIN32
    void* value = TlsGetValue(tls_index);
#else
    void* value = pthread_getspecific(tls_key);
#endif
    return (uint64_t)(uintptr_t)value; // Cast pointer back to uint64
}

char *u7_process_c_string(char *str) {
    
    printf("u7_process_c_string(): %s\n", str);
    char buf[1024];
    int len = strlen(str);
    if (len < 900) {
        sprintf(buf, "u7_process_c_string(%s)", str);
        return g_strdup(buf);
    }
    return g_strdup("string too long");
}

int u7_process_int(int value) {
    printf("u7_process_int(): %i", value);
    return value;
}

void *u7_process_u7_string(void *string) {
    U7String *u7str = (U7String *)string;

    char *cstr = u7_string_get_value(u7str);

    U7String *returnValue = u7_string_new(cstr);

    printf("u7_process_u7_string(): %p\n", cstr);
    
    return returnValue;
}
void *u7_process_g_object(void *obj) {
    printf("u7_process_u7_string(): %p", obj);
    return obj;

}

double u7_process_double(double val) {
    printf("u7_process_double(): %f", val);
    return val;
}


guint64 *u7_uint64(guint64 val) {
    guint64 *key = g_new(guint64, 1);
    *key = val;
    return key;
}
