#pragma once
#include "u7glib.h"

G_BEGIN_DECLS

#define U7_TYPE_ACTIONQUEUE (u7_actionqueue_get_type())

#define U7IsActionQueue(n) g_type_check_instance_is_a((GTypeInstance*)n, U7_TYPE_ACTIONQUEUE)

G_DECLARE_FINAL_TYPE(U7ActionQueue, u7_actionqueue, U7, ACTIONQUEUE, U7Object)

extern U7ActionQueue *u7_actionqueue_new(void);
extern void u7_actionqueue_test(void);

G_END_DECLS
