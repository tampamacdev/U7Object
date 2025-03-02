#include <glib-object.h>
#include <glib.h>
#include "u7_bridge.h"
#include "u7_api.h"
#include "u7_glib.h"

#define U7_TYPE_NOTIFICATION_CENTER (u7_notification_center_get_type())
G_DECLARE_FINAL_TYPE(U7NotificationCenter, u7_notification_center, U7, NOTIFICATION_CENTER, GObject)

// Structure definition
struct _U7NotificationCenter {
    GObject parent_instance;
    GMutex mutex;
    GHashTable *keyedThreads; // Key: uint64 thread_id, Value: U7Dictionary (placeholder)
    GHashTable *keyedObservers; // Key: uint64 thread_id, Value: U7Dictionary (placeholder)

};

G_DEFINE_TYPE(U7NotificationCenter, u7_notification_center, G_TYPE_OBJECT)

// Forward declaration of U7Dictionary (assuming it’s a GObject or struct elsewhere)
typedef struct _U7Dictionary U7Dictionary;

// GObject initialization
static void u7_notification_center_init(U7NotificationCenter *self) {
    g_mutex_init(&self->mutex);
    // Use g_hash_table_new_full for proper memory management
    self->keyedThreads = g_hash_table_new_full(g_int64_hash, g_int64_equal, g_free, g_object_unref);
    self->keyedObservers = g_hash_table_new_full(g_int64_hash, g_int64_equal, g_free, g_object_unref);
}

// GObject cleanup
static void u7_notification_center_finalize(GObject *object) {
    U7NotificationCenter *self = U7_NOTIFICATION_CENTER(object);
    
    g_hash_table_unref(self->keyedThreads);
    g_mutex_clear(&self->mutex);
    
    G_OBJECT_CLASS(u7_notification_center_parent_class)->finalize(object);
}

// GObject class initialization
static void u7_notification_center_class_init(U7NotificationCenterClass *klass) {
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->finalize = u7_notification_center_finalize;
}

// Constructor
U7NotificationCenter *u7_notification_center_new(void) {
    return NULL;
}
static U7NotificationCenter *center = NULL;

U7NotificationCenter *u7_notification_center_default(void) {
    if (center == NULL) {
        center = g_object_new(U7_TYPE_NOTIFICATION_CENTER, NULL);
    }
    //printf("u7_notification_center_default: %p\n", center);
    return center;
}

void u7_notification_center_registerThreadDispatcher(U7Object *threadDispatcher) {

    guint64 thread_id = u7_tls_get_thread_uint64_id();
    guint64 dispatcher_id = u7_object_getThreadID(threadDispatcher);

    u7_notification_center_default();

    GPtrArray *array = NULL;
    int count = 0;
    gboolean tread_eq_dispatch = (thread_id == dispatcher_id);
    gboolean passed_test = (center && thread_id && tread_eq_dispatch);

    if (passed_test) {

        array = u7_object_getObservers(threadDispatcher);

        if (array) {

            GPtrArray *observers = NULL;

            g_mutex_lock(&center->mutex);
            count = array->len;
            g_hash_table_insert(center->keyedThreads, u7_uint64(thread_id), threadDispatcher);
            g_hash_table_insert(center->keyedObservers, u7_uint64(thread_id), array);

            observers = g_hash_table_lookup(center->keyedObservers, &thread_id);
    
            g_mutex_unlock(&center->mutex);


        }


    }

    char *name = u7_object_get_name(threadDispatcher);



    g_print("register %p|center %p|t=d %i|pass %i|thread_id %" G_GUINT64_FORMAT "|dispatcher_id %" G_GUINT64_FORMAT "|array %p|count %i|name %s\n", threadDispatcher, center, tread_eq_dispatch, passed_test, thread_id, dispatcher_id, array, count, name);

    
    if (name)
        g_free(name);
}


#include <glib-object.h>

const gchar *get_class_name(GObject *instance) {
    return G_OBJECT_TYPE_NAME(instance);
}
// Instance methods
void u7_notification_center_subscribe(U7NotificationCenter *self, const gchar *name, U7Object *observer) {
    
    g_return_if_fail(U7_IS_NOTIFICATION_CENTER(self));
    g_return_if_fail(name != NULL);

    guint64 thread_id = u7_tls_get_thread_uint64_id();
    U7Object *ptr = NULL;
    int count_before = 0, count_after = 0;

    if (center && thread_id && observer) {

        u7_object_addSubscription(observer, name);

        guint64 *key = u7_uint64(thread_id);
        g_mutex_lock(&center->mutex);
        GPtrArray *observers = g_hash_table_lookup(center->keyedObservers, key);

        if (observers) {
            count_before = observers->len;

            for (int i = 0; i < observers->len; i++) {

                if ((void *)observers->pdata == (void *)observer) {
                    ptr = observer;
                    break;
                }
            }
            if (ptr == NULL)
                g_ptr_array_add(observers, observer);
            
            count_after = observers->len;

        }

        g_mutex_unlock(&center->mutex);

        g_free(key);

    }

bail:;

    g_print("subscribe|count %i -> %i|thread_id: %" G_GUINT64_FORMAT "|obs %s|name <%s>\n", count_before, count_after, thread_id, get_class_name(observer), name);


    // Empty implementation
}


struct PublishUserData {
    gchar *name;
    U7Dictionary *item;

};

void u7_retain_all_g_object(gpointer data, gpointer user_data) {
    //printf("u7_retain_all_g_object: %p\n", data);
    g_object_ref(data);
}


void u7_publish(gpointer data, gpointer user_data) {

    struct PublishUserData *info = (struct PublishUserData *)user_data;
    U7Object *obj = (U7Object *)data;
    u7_object_publish(obj, info->name, info->item);
    //g_print("obj: %p\n", obj);

}

void u7_subscribe_with_name_and_observer(const gchar *name, U7Object *observer) {


}

void u7_notification_center_publish(U7NotificationCenter *self, const gchar *name, U7Dictionary *item) {
    
    if (self == NULL) {
        g_print("u7_notification_center_publish: self is null");
        return;
    }
    
    g_return_if_fail(U7_IS_NOTIFICATION_CENTER(self));
    g_return_if_fail(name != NULL);


    guint64 thread_id = u7_tls_get_thread_uint64_id();
    U7Object *ptr = NULL;
    int count_before = 0, count_after = 0;


    U7String *str = u7_string_new(name);
    if (str) {
        u7_dictionary_add_pairs(item, "publication_name", str, NULL);
        g_object_unref(str);
    }

    if (center && thread_id) {

        GList *values = NULL;

        U7Dictionary *item_copy = u7_property_list_deep_copy(item);

        g_print("u7_notification_center_publish: %s|item_copy %p\n", name, item_copy);
        if (item_copy) {

            g_mutex_lock(&center->mutex);

            values = g_hash_table_get_values(center->keyedThreads);
            g_list_foreach(values, u7_retain_all_g_object, NULL);
            g_mutex_unlock(&center->mutex);
    
            if (values) {
                //g_print("values %i\n", (int)g_list_length(values));
                struct PublishUserData userData;
                userData.item = item_copy;
                userData.name = name;
                g_list_foreach(values, u7_publish, &userData);
                g_list_free_full(values, g_object_unref);
    
            }
    
            g_object_unref(item_copy);

        }




    }




    // Empty implementation
}