#pragma once

/*
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <math.h>
#include "mongoose.h"
#include <glib.h>
#include <glib-object.h>
#include <json-glib/json-glib.h>

extern void U7ErrorHelper(const char *format, ...);

#define U7Retain(n) g_object_ref((void *)n)
#define U7Release(n) g_object_unref((void *)n)

// Macro definition using the helper function
#ifndef U7Error
#define U7Error(n, ...) do { \
    did_bail = true; \
    U7ErrorHelper(n, ## __VA_ARGS__); \
    goto ERROR; \
} while (0)
#endif
