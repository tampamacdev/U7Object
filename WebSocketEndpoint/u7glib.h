#pragma once

#include "u7encryption.h"
#include "u7object.h"
#include "u7json.h"
#include "u7mainloop.h"
#include "u7array.h"
#include "u7string.h"
#include "u7websocketconnection.h"
#include "u7data.h"
#include "u7date.h"
#include "u7dictionary.h"
#include "u7thread.h"
#include "u7actionqueue.h"
#include "u7autoreleasepool.h"

extern char *j7_log_divider;
extern double u7_time(void);

/*
    Note: call u7glib_init(); in your main() function before using u7glib classes 
*/

extern void u7glib_init(int argc, char *argv[], char *firstKey, ...);


extern char *get_global_info_value(char *key);
extern int get_global_info_value_int(char *key);