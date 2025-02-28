#pragma once
#include "u7glib.h"

G_BEGIN_DECLS

#define U7_TYPE_DICTIONARY (u7_dictionary_get_type())

#define U7IsDictionary(n) g_type_check_instance_is_a((GTypeInstance*)n, U7_TYPE_DICTIONARY)

G_DECLARE_FINAL_TYPE(U7Dictionary, u7_dictionary, U7, DICTIONARY, U7Object)

extern U7Dictionary *u7_dictionary_new(void);
extern void u7_dictionary_test(void);

G_END_DECLS
