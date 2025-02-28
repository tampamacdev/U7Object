#include "u7array.h"
#include "u7glib.h"

struct _U7Array {
    U7Object parent_instance;
    GPtrArray *storage;
};

struct _U7ArrayClass {
    U7ObjectClass parent_class;
};

G_DEFINE_TYPE(U7Array, u7_array, U7_TYPE_OBJECT)

static void u7_array_dispose(GObject *object) {
    U7Array *array = U7_ARRAY(object);
    if (array) {
        
        if (array->storage) {
            for (guint i = 0; i < array->storage->len; i++) {

                GObject *obj = g_ptr_array_index(array->storage, i);
                U7Release(obj);

            }
            g_ptr_array_free(array->storage, false);
            array->storage = NULL;
        }
    }
    G_OBJECT_CLASS(u7_array_parent_class)->dispose(object);

}

void u7_array_add(U7Array *array, U7Object *obj) {
    if (U7IsArray(array) && U7IsObject(obj) && array->storage) {
        g_ptr_array_add(array->storage, obj);
        U7Retain(obj);
    }
}


void u7_array_remove(U7Array *array, U7Object *obj) {


}

void u7_array_remove_item_at_index(U7Array *array, guint index) {

    if (U7IsArray(array) && array->storage) {
        if (index < array->storage->len) {
            U7Object *obj = U7_OBJECT(g_ptr_array_index(array->storage, index));
            g_ptr_array_remove_index(array->storage, index);
            U7Release(obj);
        }
    }

}

void u7_array_insert(U7Array *array, U7Object *obj, guint index) {

    if (U7IsArray(array) && U7IsObject(obj) && array->storage) {
        g_ptr_array_insert(array->storage, index, obj);
        U7Retain(obj);
    }

}

U7Object *u7_array_get(U7Array *array, guint index) {

    if (U7IsArray(array) && array->storage && (index < array->storage->len)) {
        return U7_OBJECT(g_ptr_array_index(array->storage, index));
    }
    return NULL;

}

static char *u7_array_description(U7Object *obj) {

    if (U7IsArray(obj))
        return "U7Array";
    return NULL;
}

static void u7_array_class_init(U7ArrayClass *klass) {
    // Class initialization logic, if needed

    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->dispose = u7_array_dispose;
    U7ObjectClass *u7_object_class = U7_OBJECT_CLASS(klass);

    u7_object_class->description = u7_array_description;
}

static void u7_array_init(U7Array *self) {
    u7_object_set_subclass_type(U7_OBJECT(self), U7ArrayType);
    self->storage = g_ptr_array_new();
    printf("u7_array_init() parent %p self %p\n", &self->parent_instance, self);
    u7_object_print(U7_OBJECT(self));

}

U7Array *u7_array_new(void) {
    U7Array *self = g_object_new(U7_TYPE_ARRAY, NULL);
    return self;
}

void u7_array_test(void) {


    U7Array *array = u7_array_new();

    printf("u7_object_description: %s\n", U7Desc(array));

    U7Release(array);

    u7_thread_test();

    exit(0);

}

void u7_array_add_cstr(char *str) {


}