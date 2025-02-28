#include "u7json.h"

struct _U7JsonObject {
    GObject parent_instance;
};

struct _U7JsonObjectClass {
    GObjectClass parent_class;
};

G_DEFINE_TYPE(U7JsonObject, u7_jsonobject, G_TYPE_OBJECT)

static void u7_jsonobject_dispose(GObject *object) {
    printf("u7_jsonobject_dispose\n");
}

static void u7_jsonobject_class_init(U7JsonObjectClass *klass) {
    // Class initialization logic, if needed
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->dispose = u7_jsonobject_dispose;
}

static void u7_jsonobject_init(U7JsonObject *self) {
    printf("u7_jsonobject_init\n");
}

U7JsonObject *u7_jsonobject_new(void) {
    U7JsonObject *self = g_object_new(U7_TYPE_JSONOBJECT, NULL);
    return self;
}

void u7_jsonobject_test(void) {

    U7JsonObject *jsonobject = u7_jsonobject_new();
    U7Release(jsonobject);
    printf("u7_jsonobject_test()|jsonobject %p\n", jsonobject);

}