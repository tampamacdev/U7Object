#pragma once


#include "u7glib.h"



G_BEGIN_DECLS

#define U7_TYPE_JSONOBJECT (u7_jsonobject_get_type())

G_DECLARE_FINAL_TYPE(U7JsonObject, u7_jsonobject, U7, JSONOBJECT, GObject)

extern U7JsonObject *u7_jsonobject_new(void);
extern void u7_jsonobject_test(void);

G_END_DECLS
