#include "u7actionqueue.h"

struct _U7ActionQueue {
    U7Object parent_instance;
};

struct _U7ActionQueueClass {
    U7ObjectClass parent_class;
};

G_DEFINE_TYPE(U7ActionQueue, u7_actionqueue, U7_TYPE_OBJECT)

static void u7_actionqueue_dispose(GObject *object) {
    printf("u7_actionqueue_dispose\n");

    G_OBJECT_CLASS(u7_actionqueue_parent_class)->dispose(object);

}

static char *u7_actionqueue_description(U7Object *obj) {
    if (U7IsActionQueue(obj)) 
        return "u7_actionqueue_description need to implement";
    return "u7_actionqueue_description";
}

static void u7_actionqueue_class_init(U7ActionQueueClass *klass) {
    // Class initialization logic, if needed
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->dispose = u7_actionqueue_dispose;

    U7ObjectClass *u7_object_class = U7_OBJECT_CLASS(klass);
    u7_object_class->description = u7_actionqueue_description;

}

static void u7_actionqueue_init(U7ActionQueue *self) {
    u7_object_set_subclass_type(U7_OBJECT(self), U7ActionQueueType);

    printf("u7_actionqueue_init\n");
}

U7ActionQueue *u7_actionqueue_new(void) {
    U7ActionQueue *self = g_object_new(U7_TYPE_ACTIONQUEUE, NULL);
    return self;
}

void u7_actionqueue_test(void) {

    U7ActionQueue *actionqueue = u7_actionqueue_new();
    printf("u7_actionqueue_test()|actionqueue %p\n", actionqueue);
    U7Release(actionqueue);

}


