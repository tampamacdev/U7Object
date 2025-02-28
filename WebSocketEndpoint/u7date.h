#pragma once
#include "u7glib.h"

G_BEGIN_DECLS

#define U7_TYPE_DATE (u7_date_get_type())

#define U7IsDate(n) g_type_check_instance_is_a((GTypeInstance*)n, U7_TYPE_DATE)

G_DECLARE_FINAL_TYPE(U7Date, u7_date, U7, DATE, U7Object)

extern U7Date *u7_date_new(void);
extern void u7_date_test(void);

G_END_DECLS
