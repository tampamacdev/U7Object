#include "u7object.h"


typedef struct {
    U7ObjectSubclassType subclass_type;
} U7ObjectPrivate;

#define U7OBJECT_TRACK_MEMORY 

static GMutex u7_object_alloc_dealloc_lock;
static guint64 u7_object_count = 0;

G_DEFINE_TYPE_WITH_PRIVATE(U7Object, u7_object, G_TYPE_OBJECT)


static void u7_object_dispose(GObject *object) {
    //printf("u7_object_dispose(%p): %s\n", object, U7Desc(object));
    G_OBJECT_CLASS(u7_object_parent_class)->dispose(object);

}

static void u7_object_finalize(GObject *object) {
    
#ifdef U7OBJECT_TRACK_MEMORY
    g_mutex_lock(&u7_object_alloc_dealloc_lock);
    u7_object_count--;
    g_mutex_unlock(&u7_object_alloc_dealloc_lock);
#endif


    printf("u7_object_finalize(%p)|u7_object_count %lli %s\n", object, (long long int)u7_object_count, U7Desc(object));
    G_OBJECT_CLASS(u7_object_parent_class)->finalize(object);
}

void u7_object_set_subclass_type(U7Object *obj, U7ObjectSubclassType type) {

    if (obj) {
        U7ObjectPrivate *priv = u7_object_get_instance_private(obj);
        if (priv)
            priv->subclass_type = type;
    }
}

static void u7_object_class_init(U7ObjectClass *klass) {
    // Class initialization logic, if needed
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->dispose = u7_object_dispose;
    object_class->finalize = u7_object_finalize;

    g_mutex_init(&u7_object_alloc_dealloc_lock);

}

static void u7_object_init(U7Object *self) {

    U7ObjectPrivate *priv = u7_object_get_instance_private(self);


#ifdef U7OBJECT_TRACK_MEMORY
    g_mutex_lock(&u7_object_alloc_dealloc_lock);
    u7_object_count++;
    g_mutex_unlock(&u7_object_alloc_dealloc_lock);
#endif



    //printf("u7_object_init() %p\n", self);
}


char *u7_subtype_name(U7Object *obj) {

    U7ObjectPrivate *priv = u7_object_get_instance_private(obj);

    if (priv == NULL)
        return "<null object>";

    switch (priv->subclass_type) {
             
        case U7StringType: return "U7StringType";
        case U7DictionaryType: return "U7DictionaryType";
        case U7ArrayType: return "U7ArrayType";
        case U7JsonType: return "U7JsonType";
        case U7WebSocketConnectionType: return "U7WebSocketConnectionType";
        case U7DateType: return "U7DateType";
        case U7DataType: return "U7DataType";
        default: break;
    }
    return "UNKNOWN_TYPE";
}


void u7_object_print(U7Object *obj) {
    
    U7ObjectPrivate *priv = u7_object_get_instance_private(obj);
    printf("u7_object_print()|%s\n", u7_subtype_name(obj));


}

U7Object *u7_object_new(void) {
    U7Object *self = g_object_new(U7_TYPE_OBJECT, NULL);
    return self;
}

void u7_object_test(void) {

    U7Object *object = u7_object_new();
    U7Release(object);
    printf("u7_object_test()|object %p\n", object);

}

char *u7_object_description(U7Object *obj) {

    U7ObjectClass *klass = U7_OBJECT_GET_CLASS(obj);

    if (klass->description) {

        return klass->description(obj);
    }

    return NULL;
}
