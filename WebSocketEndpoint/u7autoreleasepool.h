#pragma once
#include "u7glib.h"

G_BEGIN_DECLS

#define U7_TYPE_AUTORELEASEPOOL (u7_autoreleasepool_get_type())

#define U7IsAutoreleasePool(n) g_type_check_instance_is_a((GTypeInstance*)n, U7_TYPE_AUTORELEASEPOOL)

G_DECLARE_FINAL_TYPE(U7AutoreleasePool, u7_autoreleasepool, U7, AUTORELEASEPOOL, U7Object)

extern U7AutoreleasePool *u7_autoreleasepool_new(void);
extern void u7_autoreleasepool_test(void);

G_END_DECLS
