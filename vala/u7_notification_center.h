#ifndef U7_NOTIFICATION_CENTER_H
#define U7_NOTIFICATION_CENTER_H

#include <glib-object.h>

// GObject type macros
#define U7_TYPE_NOTIFICATION_CENTER (u7_notification_center_get_type())
#define U7_NOTIFICATION_CENTER(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), U7_TYPE_NOTIFICATION_CENTER, U7NotificationCenter))
#define U7_IS_NOTIFICATION_CENTER(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), U7_TYPE_NOTIFICATION_CENTER))
#define U7_NOTIFICATION_CENTER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), U7_TYPE_NOTIFICATION_CENTER, U7NotificationCenterClass))
#define U7_IS_NOTIFICATION_CENTER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), U7_TYPE_NOTIFICATION_CENTER))
#define U7_NOTIFICATION_CENTER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj), U7_TYPE_NOTIFICATION_CENTER, U7NotificationCenterClass))

// Forward declaration of U7Dictionary (assumed to be a GObject or struct)
typedef struct _U7Dictionary U7Dictionary;
typedef struct _U7Object U7Object;

// Structure definitions
typedef struct _U7NotificationCenter U7NotificationCenter;
typedef struct _U7NotificationCenterClass U7NotificationCenterClass;

struct _U7NotificationCenter {
    GObject parent_instance;
    GMutex mutex;
    GHashTable *subscriptions; // Key: uint64 thread_id, Value: U7Dictionary
};

struct _U7NotificationCenterClass {
    GObjectClass parent_class;
    /* Future virtual methods could go here */
};

// Function declarations
GType u7_notification_center_get_type(void) G_GNUC_CONST;
U7NotificationCenter *u7_notification_center_new(void);
U7NotificationCenter *u7_notification_center_default(void);

void u7_notification_center_subscribe(U7NotificationCenter *self, const gchar *name, U7Object *observer);
void u7_notification_center_publish(U7NotificationCenter *self, const gchar *name, U7Dictionary *item);
void u7_notification_center_registerThreadDispatcher(U7Object *threadDispatcher);



#endif /* U7_NOTIFICATION_CENTER_H */