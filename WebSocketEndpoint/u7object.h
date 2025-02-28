#pragma once
#include "u7shared.h"

G_BEGIN_DECLS


typedef enum {
    U7StringType = 1,
    U7DictionaryType,
    U7ArrayType,
    U7JsonType,
    U7WebSocketConnectionType,
    U7DateType,
    U7DataType,
    U7ThreadType,
    U7AutoreleasePoolType,
    U7ActionQueueType
} U7ObjectSubclassType;


#define U7_TYPE_OBJECT (u7_object_get_type())

G_DECLARE_DERIVABLE_TYPE(U7Object, u7_object, U7, OBJECT, GObject)

typedef char * (*U7ObjectDescription)(U7Object *obj);

struct _U7ObjectClass {

    GObjectClass parent_class;

    U7ObjectDescription description;
    gpointer padding[16];

};

extern char *u7_subtype_name(U7Object *obj);
extern U7Object *u7_object_new(void);
extern void u7_object_set_subclass_type(U7Object *obj, U7ObjectSubclassType type);
#define U7IsObject(n) g_type_check_instance_is_a((GTypeInstance*)n, U7_TYPE_OBJECT)
extern void u7_object_test(void);
extern void u7_object_print(U7Object *obj);
#define U7Desc(n) u7_object_description(U7_OBJECT(n))
extern char *u7_object_description(U7Object *obj);

G_END_DECLS
