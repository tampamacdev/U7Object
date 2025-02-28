#include "u7thread.h"

static U7Thread *main_thread = NULL;


struct _U7Thread {
    U7Object parent_instance;
    void* (*start_routine)(void*);
    U7AutoreleasePool *autorelease_pool;
    U7Dictionary *info;
};

//__thread U7Thread *tlm_thread_object = NULL;     // Thread-Local Storage for U7Thread object for thread


struct _U7ThreadClass {
    U7ObjectClass parent_class;
};

G_DEFINE_TYPE(U7Thread, u7_thread, U7_TYPE_OBJECT)

static void u7_thread_dispose(GObject *object) {
    printf("u7_thread_dispose\n");

    U7Thread *thread = U7_THREAD(object);
    if (thread) {
        if (thread->autorelease_pool) {
            U7Release(thread->autorelease_pool);
            thread->autorelease_pool = NULL;
        }
        if (thread->info) {
            U7Release(thread->info);
            thread->info = NULL;
        }

    }

    G_OBJECT_CLASS(u7_thread_parent_class)->dispose(object);

}

static char *u7_thread_description(U7Object *obj) {
    if (U7IsThread(obj)) 
        return "u7_thread_description need to implement";
    return "u7_thread_description";
}

static void u7_thread_class_init(U7ThreadClass *klass) {
    // Class initialization logic, if needed
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->dispose = u7_thread_dispose;

    U7ObjectClass *u7_object_class = U7_OBJECT_CLASS(klass);
    u7_object_class->description = u7_thread_description;

}

static void u7_thread_init(U7Thread *self) {

    u7_object_set_subclass_type(U7_OBJECT(self), U7ThreadType);


}

U7Thread *u7_thread_new(void* (*start_routine)(void*)) {
    U7Thread *self = g_object_new(U7_TYPE_THREAD, NULL);
    if (self) {
        self->start_routine = start_routine;
        self->autorelease_pool = u7_autoreleasepool_new();
    }
    return self;
}


void u7_thread_test(void) {

    U7Thread *thread = u7_thread_new(NULL);
    printf("u7_thread_test()|thread %p\n", thread);
    U7Release(thread);

}

void u7_thread_main_init(void) {

    main_thread = u7_thread_new(NULL);

    printf("u7_thread_main_init()|main_thread %p\n", main_thread);

}



