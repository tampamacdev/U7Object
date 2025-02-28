#pragma once
#include "u7glib.h"

G_BEGIN_DECLS

#define U7_TYPE_THREAD (u7_thread_get_type())

#define U7IsThread(n) g_type_check_instance_is_a((GTypeInstance*)n, U7_TYPE_THREAD)

G_DECLARE_FINAL_TYPE(U7Thread, u7_thread, U7, THREAD, U7Object)

extern U7Thread *u7_thread_new(void* (*start_routine)(void*));
extern void u7_thread_test(void);
extern void u7_thread_main_init(void);
G_END_DECLS
