#pragma once

#include "u7glib.h"

/*
    retain and release U7Array with g_object_ref() and g_object_unref()
*/


G_BEGIN_DECLS

#define U7_TYPE_ARRAY (u7_array_get_type())
#define U7IsArray(n) g_type_check_instance_is_a((GTypeInstance*)n, U7_TYPE_ARRAY)

G_DECLARE_FINAL_TYPE(U7Array, u7_array, U7, ARRAY, U7Object)

extern U7Array *u7_array_new(void);
extern void u7_array_test(void);
extern void u7_array_add_cstr(char *str);
extern void u7_array_add(U7Array *array, U7Object *obj);
extern void u7_array_remove(U7Array *array, U7Object *obj);
extern void u7_array_remove_item_at_index(U7Array *array, guint index);

extern void u7_array_insert(U7Array *array, U7Object *obj, guint index);
extern U7Object *u7_array_get(U7Array *array, guint index);


G_END_DECLS

