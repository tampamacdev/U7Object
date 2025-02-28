#include "u7autoreleasepool.h"

struct _U7AutoreleasePool {
    U7Object parent_instance;
};

struct _U7AutoreleasePoolClass {
    U7ObjectClass parent_class;
};

G_DEFINE_TYPE(U7AutoreleasePool, u7_autoreleasepool, U7_TYPE_OBJECT)

static void u7_autoreleasepool_dispose(GObject *object) {
    printf("u7_autoreleasepool_dispose\n");

    G_OBJECT_CLASS(u7_autoreleasepool_parent_class)->dispose(object);

}

static char *u7_autoreleasepool_description(U7Object *obj) {
    if (U7IsAutoreleasePool(obj)) 
        return "u7_autoreleasepool_description need to implement";
    return "u7_autoreleasepool_description";
}

static void u7_autoreleasepool_class_init(U7AutoreleasePoolClass *klass) {
    // Class initialization logic, if needed
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->dispose = u7_autoreleasepool_dispose;

    U7ObjectClass *u7_object_class = U7_OBJECT_CLASS(klass);
    u7_object_class->description = u7_autoreleasepool_description;

}

static void u7_autoreleasepool_init(U7AutoreleasePool *self) {
    u7_object_set_subclass_type(U7_OBJECT(self), U7AutoreleasePoolType);

    printf("u7_autoreleasepool_init\n");
}

U7AutoreleasePool *u7_autoreleasepool_new(void) {
    U7AutoreleasePool *self = g_object_new(U7_TYPE_AUTORELEASEPOOL, NULL);
    return self;
}

void u7_autoreleasepool_test(void) {

    U7AutoreleasePool *autoreleasepool = u7_autoreleasepool_new();
    printf("u7_autoreleasepool_test()|autoreleasepool %p\n", autoreleasepool);
    U7Release(autoreleasepool);

}


