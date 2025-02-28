#include "u7date.h"

struct _U7Date {
    U7Object parent_instance;
};

struct _U7DateClass {
    U7ObjectClass parent_class;
};

G_DEFINE_TYPE(U7Date, u7_date, U7_TYPE_OBJECT)

static void u7_date_dispose(GObject *object) {
    printf("u7_date_dispose\n");

    G_OBJECT_CLASS(u7_date_parent_class)->dispose(object);

}

static char *u7_date_description(U7Object *obj) {
    if (U7IsDate(obj)) 
        return "u7_date_description need to implement";
    return "u7_date_description";
}

static void u7_date_class_init(U7DateClass *klass) {
    // Class initialization logic, if needed
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->dispose = u7_date_dispose;

    U7ObjectClass *u7_object_class = U7_OBJECT_CLASS(klass);
    u7_object_class->description = u7_date_description;

}

static void u7_date_init(U7Date *self) {
    u7_object_set_subclass_type(U7_OBJECT(self), U7DateType);
    printf("u7_date_init\n");
}

U7Date *u7_date_new(void) {
    U7Date *self = g_object_new(U7_TYPE_DATE, NULL);
    return self;
}

void u7_date_test(void) {

    U7Date *date = u7_date_new();
    printf("u7_date_test()|date %p\n", date);
    U7Release(date);

}


