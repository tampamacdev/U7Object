#include "u7data.h"

struct _U7Data {
    U7Object parent_instance;
};

struct _U7DataClass {
    U7ObjectClass parent_class;
};

G_DEFINE_TYPE(U7Data, u7_data, U7_TYPE_OBJECT)

static void u7_data_dispose(GObject *object) {
    printf("u7_data_dispose\n");

    G_OBJECT_CLASS(u7_data_parent_class)->dispose(object);

}

static char *u7_data_description(U7Object *obj) {
    if (U7IsData(obj)) 
        return "u7_data_description need to implement";
    return "u7_data_description";
}

static void u7_data_class_init(U7DataClass *klass) {
    // Class initialization logic, if needed
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->dispose = u7_data_dispose;

    U7ObjectClass *u7_object_class = U7_OBJECT_CLASS(klass);
    u7_object_class->description = u7_data_description;

}

static void u7_data_init(U7Data *self) {
    u7_object_set_subclass_type(U7_OBJECT(self), U7DataType);
    printf("u7_data_init\n");
}

U7Data *u7_data_new(void) {
    U7Data *self = g_object_new(U7_TYPE_DATA, NULL);
    return self;
}

void u7_data_test(void) {

    U7Data *data = u7_data_new();
    printf("u7_data_test()|data %p\n", data);
    U7Release(data);

}


