#pragma once
#include "u7glib.h"

G_BEGIN_DECLS

#define U7_TYPE_DATA (u7_data_get_type())

#define U7IsData(n) g_type_check_instance_is_a((GTypeInstance*)n, U7_TYPE_DATA)

G_DECLARE_FINAL_TYPE(U7Data, u7_data, U7, DATA, U7Object)

extern U7Data *u7_data_new(void);
extern void u7_data_test(void);

G_END_DECLS
