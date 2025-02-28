#include "u7dictionary.h"

struct _U7Dictionary {
    U7Object parent_instance;
};

struct _U7DictionaryClass {
    U7ObjectClass parent_class;
};

G_DEFINE_TYPE(U7Dictionary, u7_dictionary, U7_TYPE_OBJECT)

static void u7_dictionary_dispose(GObject *object) {
    printf("u7_dictionary_dispose\n");

    G_OBJECT_CLASS(u7_dictionary_parent_class)->dispose(object);

}

static char *u7_dictionary_description(U7Object *obj) {
    if (U7IsDictionary(obj)) 
        return "u7_dictionary_description need to implement";
    return "u7_dictionary_description";
}

static void u7_dictionary_class_init(U7DictionaryClass *klass) {
    // Class initialization logic, if needed
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->dispose = u7_dictionary_dispose;

    U7ObjectClass *u7_object_class = U7_OBJECT_CLASS(klass);
    u7_object_class->description = u7_dictionary_description;

}

static void u7_dictionary_init(U7Dictionary *self) {
    printf("u7_dictionary_init\n");
}

U7Dictionary *u7_dictionary_new(void) {
    U7Dictionary *self = g_object_new(U7_TYPE_DICTIONARY, NULL);
    return self;
}

void u7_dictionary_test(void) {

    U7Dictionary *dictionary = u7_dictionary_new();
    printf("u7_dictionary_test()|dictionary %p\n", dictionary);
    U7Release(dictionary);

}


