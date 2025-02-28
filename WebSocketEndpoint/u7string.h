#pragma once
#include "u7glib.h"

G_BEGIN_DECLS

#define U7_TYPE_STRING (u7_string_get_type())

G_DECLARE_FINAL_TYPE(U7String, u7_string, U7, STRING, U7Object)

#define U7Str(n) u7_string_getCString(n)

#define U7IsString(n) g_type_check_instance_is_a((GTypeInstance*)n, U7_TYPE_STRING)

extern U7String *u7_string_new(char *str);
extern void u7_string_test(void);
extern char *u7_string_getCString(U7String *string);
extern gboolean u7_string_is_member(U7Object *obj);
extern char *u7_timestamp_create(void);
extern char *u7_hms(char *buf, double time);
extern gboolean u7_cstrings_are_equal(const char *str1, int str1_len, const char *trimmed_str2, int str2_len);
G_END_DECLS
