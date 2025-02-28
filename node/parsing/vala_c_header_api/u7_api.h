/* u7_api.h generated by valac 0.48.6, the Vala compiler, do not modify */

#ifndef __U7_API_H__
#define __U7_API_H__

#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <json-glib/json-glib.h>
#include <float.h>
#include <math.h>
#include <gee.h>

G_BEGIN_DECLS

#define TYPE_U7_OBJECT (u7_object_get_type ())
#define U7_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_U7_OBJECT, U7Object))
#define U7_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_U7_OBJECT, U7ObjectClass))
#define IS_U7_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_U7_OBJECT))
#define IS_U7_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_U7_OBJECT))
#define U7_OBJECT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_U7_OBJECT, U7ObjectClass))

typedef struct _U7Object U7Object;
typedef struct _U7ObjectClass U7ObjectClass;
typedef struct _U7ObjectPrivate U7ObjectPrivate;

#define TYPE_U7_NOTIFICATION_CENTER (u7_notification_center_get_type ())
#define U7_NOTIFICATION_CENTER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_U7_NOTIFICATION_CENTER, U7NotificationCenter))
#define U7_NOTIFICATION_CENTER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_U7_NOTIFICATION_CENTER, U7NotificationCenterClass))
#define IS_U7_NOTIFICATION_CENTER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_U7_NOTIFICATION_CENTER))
#define IS_U7_NOTIFICATION_CENTER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_U7_NOTIFICATION_CENTER))
#define U7_NOTIFICATION_CENTER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_U7_NOTIFICATION_CENTER, U7NotificationCenterClass))

typedef struct _U7NotificationCenter U7NotificationCenter;
typedef struct _U7NotificationCenterClass U7NotificationCenterClass;
typedef struct _U7NotificationCenterPrivate U7NotificationCenterPrivate;

#define TYPE_U7_PROPERTY_LIST (u7_property_list_get_type ())
#define U7_PROPERTY_LIST(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_U7_PROPERTY_LIST, U7PropertyList))
#define U7_PROPERTY_LIST_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_U7_PROPERTY_LIST, U7PropertyListClass))
#define IS_U7_PROPERTY_LIST(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_U7_PROPERTY_LIST))
#define IS_U7_PROPERTY_LIST_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_U7_PROPERTY_LIST))
#define U7_PROPERTY_LIST_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_U7_PROPERTY_LIST, U7PropertyListClass))

typedef struct _U7PropertyList U7PropertyList;
typedef struct _U7PropertyListClass U7PropertyListClass;

#define TYPE_U7_THREAD_NOTIFICATION_CENTER (u7_thread_notification_center_get_type ())
#define U7_THREAD_NOTIFICATION_CENTER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_U7_THREAD_NOTIFICATION_CENTER, U7ThreadNotificationCenter))
#define U7_THREAD_NOTIFICATION_CENTER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_U7_THREAD_NOTIFICATION_CENTER, U7ThreadNotificationCenterClass))
#define IS_U7_THREAD_NOTIFICATION_CENTER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_U7_THREAD_NOTIFICATION_CENTER))
#define IS_U7_THREAD_NOTIFICATION_CENTER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_U7_THREAD_NOTIFICATION_CENTER))
#define U7_THREAD_NOTIFICATION_CENTER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_U7_THREAD_NOTIFICATION_CENTER, U7ThreadNotificationCenterClass))

typedef struct _U7ThreadNotificationCenter U7ThreadNotificationCenter;
typedef struct _U7ThreadNotificationCenterClass U7ThreadNotificationCenterClass;
typedef struct _U7ThreadNotificationCenterPrivate U7ThreadNotificationCenterPrivate;

#define TYPE_U7_DISTRIBUTED_NOTIFICATION_CENTER (u7_distributed_notification_center_get_type ())
#define U7_DISTRIBUTED_NOTIFICATION_CENTER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_U7_DISTRIBUTED_NOTIFICATION_CENTER, U7DistributedNotificationCenter))
#define U7_DISTRIBUTED_NOTIFICATION_CENTER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_U7_DISTRIBUTED_NOTIFICATION_CENTER, U7DistributedNotificationCenterClass))
#define IS_U7_DISTRIBUTED_NOTIFICATION_CENTER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_U7_DISTRIBUTED_NOTIFICATION_CENTER))
#define IS_U7_DISTRIBUTED_NOTIFICATION_CENTER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_U7_DISTRIBUTED_NOTIFICATION_CENTER))
#define U7_DISTRIBUTED_NOTIFICATION_CENTER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_U7_DISTRIBUTED_NOTIFICATION_CENTER, U7DistributedNotificationCenterClass))

typedef struct _U7DistributedNotificationCenter U7DistributedNotificationCenter;
typedef struct _U7DistributedNotificationCenterClass U7DistributedNotificationCenterClass;
typedef struct _U7DistributedNotificationCenterPrivate U7DistributedNotificationCenterPrivate;
typedef struct _U7PropertyListPrivate U7PropertyListPrivate;

#define TYPE_U7_STRING (u7_string_get_type ())
#define U7_STRING(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_U7_STRING, U7String))
#define U7_STRING_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_U7_STRING, U7StringClass))
#define IS_U7_STRING(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_U7_STRING))
#define IS_U7_STRING_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_U7_STRING))
#define U7_STRING_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_U7_STRING, U7StringClass))

typedef struct _U7String U7String;
typedef struct _U7StringClass U7StringClass;
typedef struct _U7StringPrivate U7StringPrivate;

#define TYPE_U7_NUMBER (u7_number_get_type ())
#define U7_NUMBER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_U7_NUMBER, U7Number))
#define U7_NUMBER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_U7_NUMBER, U7NumberClass))
#define IS_U7_NUMBER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_U7_NUMBER))
#define IS_U7_NUMBER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_U7_NUMBER))
#define U7_NUMBER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_U7_NUMBER, U7NumberClass))

typedef struct _U7Number U7Number;
typedef struct _U7NumberClass U7NumberClass;
typedef struct _U7NumberPrivate U7NumberPrivate;
typedef enum  {
	U7_NUMBER_NUMBER_TYPE_INT,
	U7_NUMBER_NUMBER_TYPE_DOUBLE,
	U7_NUMBER_NUMBER_TYPE_BOOL
} U7NumberNumberType;

#define U7_NUMBER_TYPE_NUMBER_TYPE (u7_number_number_type_get_type ())

#define TYPE_U7_ARRAY (u7_array_get_type ())
#define U7_ARRAY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_U7_ARRAY, U7Array))
#define U7_ARRAY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_U7_ARRAY, U7ArrayClass))
#define IS_U7_ARRAY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_U7_ARRAY))
#define IS_U7_ARRAY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_U7_ARRAY))
#define U7_ARRAY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_U7_ARRAY, U7ArrayClass))

typedef struct _U7Array U7Array;
typedef struct _U7ArrayClass U7ArrayClass;
typedef struct _U7ArrayPrivate U7ArrayPrivate;

#define TYPE_U7_THREAD_LOOP (u7_thread_loop_get_type ())
#define U7_THREAD_LOOP(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_U7_THREAD_LOOP, U7ThreadLoop))
#define U7_THREAD_LOOP_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_U7_THREAD_LOOP, U7ThreadLoopClass))
#define IS_U7_THREAD_LOOP(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_U7_THREAD_LOOP))
#define IS_U7_THREAD_LOOP_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_U7_THREAD_LOOP))
#define U7_THREAD_LOOP_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_U7_THREAD_LOOP, U7ThreadLoopClass))

typedef struct _U7ThreadLoop U7ThreadLoop;
typedef struct _U7ThreadLoopClass U7ThreadLoopClass;
typedef struct _U7ThreadLoopPrivate U7ThreadLoopPrivate;

#define TYPE_U7_KEYBOARD_INPUT_MONITOR (u7_keyboard_input_monitor_get_type ())
#define U7_KEYBOARD_INPUT_MONITOR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_U7_KEYBOARD_INPUT_MONITOR, U7KeyboardInputMonitor))
#define U7_KEYBOARD_INPUT_MONITOR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_U7_KEYBOARD_INPUT_MONITOR, U7KeyboardInputMonitorClass))
#define IS_U7_KEYBOARD_INPUT_MONITOR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_U7_KEYBOARD_INPUT_MONITOR))
#define IS_U7_KEYBOARD_INPUT_MONITOR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_U7_KEYBOARD_INPUT_MONITOR))
#define U7_KEYBOARD_INPUT_MONITOR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_U7_KEYBOARD_INPUT_MONITOR, U7KeyboardInputMonitorClass))

typedef struct _U7KeyboardInputMonitor U7KeyboardInputMonitor;
typedef struct _U7KeyboardInputMonitorClass U7KeyboardInputMonitorClass;
typedef struct _U7KeyboardInputMonitorPrivate U7KeyboardInputMonitorPrivate;

#define TYPE_U7_DICTIONARY (u7_dictionary_get_type ())
#define U7_DICTIONARY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_U7_DICTIONARY, U7Dictionary))
#define U7_DICTIONARY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_U7_DICTIONARY, U7DictionaryClass))
#define IS_U7_DICTIONARY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_U7_DICTIONARY))
#define IS_U7_DICTIONARY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_U7_DICTIONARY))
#define U7_DICTIONARY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_U7_DICTIONARY, U7DictionaryClass))

typedef struct _U7Dictionary U7Dictionary;
typedef struct _U7DictionaryClass U7DictionaryClass;
typedef struct _U7DictionaryPrivate U7DictionaryPrivate;

#define TYPE_U7_DATE (u7_date_get_type ())
#define U7_DATE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_U7_DATE, U7Date))
#define U7_DATE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_U7_DATE, U7DateClass))
#define IS_U7_DATE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_U7_DATE))
#define IS_U7_DATE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_U7_DATE))
#define U7_DATE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_U7_DATE, U7DateClass))

typedef struct _U7Date U7Date;
typedef struct _U7DateClass U7DateClass;
typedef struct _U7DatePrivate U7DatePrivate;

#define TYPE_U7_DATA (u7_data_get_type ())
#define U7_DATA(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_U7_DATA, U7Data))
#define U7_DATA_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_U7_DATA, U7DataClass))
#define IS_U7_DATA(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_U7_DATA))
#define IS_U7_DATA_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_U7_DATA))
#define U7_DATA_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_U7_DATA, U7DataClass))

typedef struct _U7Data U7Data;
typedef struct _U7DataClass U7DataClass;
typedef struct _U7DataPrivate U7DataPrivate;

struct _U7Object {
	GObject parent_instance;
	U7ObjectPrivate * priv;
};

struct _U7ObjectClass {
	GObjectClass parent_class;
	gchar* (*to_string) (U7Object* self);
};

struct _U7NotificationCenter {
	U7Object parent_instance;
	U7NotificationCenterPrivate * priv;
};

struct _U7NotificationCenterClass {
	U7ObjectClass parent_class;
};

struct _U7ThreadNotificationCenter {
	U7NotificationCenter parent_instance;
	U7ThreadNotificationCenterPrivate * priv;
};

struct _U7ThreadNotificationCenterClass {
	U7NotificationCenterClass parent_class;
};

struct _U7DistributedNotificationCenter {
	U7ThreadNotificationCenter parent_instance;
	U7DistributedNotificationCenterPrivate * priv;
};

struct _U7DistributedNotificationCenterClass {
	U7ThreadNotificationCenterClass parent_class;
};

struct _U7PropertyList {
	U7Object parent_instance;
	U7PropertyListPrivate * priv;
};

struct _U7PropertyListClass {
	U7ObjectClass parent_class;
	U7PropertyList* (*deep_copy) (U7PropertyList* self);
	JsonNode* (*to_json) (U7PropertyList* self);
};

struct _U7String {
	U7PropertyList parent_instance;
	U7StringPrivate * priv;
};

struct _U7StringClass {
	U7PropertyListClass parent_class;
};

struct _U7Number {
	U7PropertyList parent_instance;
	U7NumberPrivate * priv;
};

struct _U7NumberClass {
	U7PropertyListClass parent_class;
};

struct _U7Array {
	U7PropertyList parent_instance;
	U7ArrayPrivate * priv;
};

struct _U7ArrayClass {
	U7PropertyListClass parent_class;
};

struct _U7ThreadLoop {
	U7Object parent_instance;
	U7ThreadLoopPrivate * priv;
	GThread* current_thread;
	GMainContext* context;
	GMainLoop* loop;
	GAsyncQueue* queue;
};

struct _U7ThreadLoopClass {
	U7ObjectClass parent_class;
	void (*threadEntry) (U7ThreadLoop* self, U7PropertyList* info);
	void (*threadSetup) (U7ThreadLoop* self);
};

struct _U7KeyboardInputMonitor {
	U7ThreadLoop parent_instance;
	U7KeyboardInputMonitorPrivate * priv;
};

struct _U7KeyboardInputMonitorClass {
	U7ThreadLoopClass parent_class;
};

struct _U7Dictionary {
	U7PropertyList parent_instance;
	U7DictionaryPrivate * priv;
};

struct _U7DictionaryClass {
	U7PropertyListClass parent_class;
};

struct _U7Date {
	U7PropertyList parent_instance;
	U7DatePrivate * priv;
};

struct _U7DateClass {
	U7PropertyListClass parent_class;
};

struct _U7Data {
	U7PropertyList parent_instance;
	U7DataPrivate * priv;
};

struct _U7DataClass {
	U7PropertyListClass parent_class;
};

typedef enum  {
	U7_ERROR_INVALID_FORMAT
} U7Error;
#define U7_ERROR u7_error_quark ()

GType u7_object_get_type (void) G_GNUC_CONST;
G_DEFINE_AUTOPTR_CLEANUP_FUNC (U7Object, g_object_unref)
GType u7_notification_center_get_type (void) G_GNUC_CONST;
G_DEFINE_AUTOPTR_CLEANUP_FUNC (U7NotificationCenter, g_object_unref)
void u7_notification_center_init (void);
U7NotificationCenter* u7_notification_center_new (void);
U7NotificationCenter* u7_notification_center_construct (GType object_type);
GType u7_property_list_get_type (void) G_GNUC_CONST;
G_DEFINE_AUTOPTR_CLEANUP_FUNC (U7PropertyList, g_object_unref)
void u7_notification_center_publishThread (U7NotificationCenter* self,
                                           const gchar* publisher,
                                           U7PropertyList* post);
void u7_notification_center_publishProcess (U7NotificationCenter* self,
                                            const gchar* publisher,
                                            U7PropertyList* post);
void u7_notification_center_publishNetwork (U7NotificationCenter* self,
                                            const gchar* publisher,
                                            U7PropertyList* post);
GType u7_thread_notification_center_get_type (void) G_GNUC_CONST;
G_DEFINE_AUTOPTR_CLEANUP_FUNC (U7ThreadNotificationCenter, g_object_unref)
void u7_thread_notification_center_init (void);
U7ThreadNotificationCenter* u7_thread_notification_center_new (void);
U7ThreadNotificationCenter* u7_thread_notification_center_construct (GType object_type);
U7ThreadNotificationCenter* u7_thread_notification_center_get_default (void);
GType u7_distributed_notification_center_get_type (void) G_GNUC_CONST;
G_DEFINE_AUTOPTR_CLEANUP_FUNC (U7DistributedNotificationCenter, g_object_unref)
void u7_distributed_notification_center_init (void);
U7DistributedNotificationCenter* u7_distributed_notification_center_new (void);
U7DistributedNotificationCenter* u7_distributed_notification_center_construct (GType object_type);
void u7_object_init (void);
U7Object* u7_object_new (void);
U7Object* u7_object_construct (GType object_type);
gchar* u7_object_to_string (U7Object* self);
gint u7_object_get_instance_count (void);
gint u7_object_get_class_instance_count (const gchar* class_name);
gchar* u7_object_get_class_name (U7Object* self);
gchar* u7_object_get_all_class_instance_counts_report (void);
const gchar* u7_object_get_u7object_type (U7Object* self);
GType u7_string_get_type (void) G_GNUC_CONST;
G_DEFINE_AUTOPTR_CLEANUP_FUNC (U7String, g_object_unref)
U7String* u7_string_new (const gchar* value);
U7String* u7_string_construct (GType object_type,
                               const gchar* value);
const gchar* u7_string_get_value (U7String* self);
GType u7_number_get_type (void) G_GNUC_CONST;
G_DEFINE_AUTOPTR_CLEANUP_FUNC (U7Number, g_object_unref)
GType u7_number_number_type_get_type (void) G_GNUC_CONST;
U7Number* u7_number_new_from_int (gint value);
U7Number* u7_number_construct_from_int (GType object_type,
                                        gint value);
U7Number* u7_number_new_from_double (gdouble value);
U7Number* u7_number_construct_from_double (GType object_type,
                                           gdouble value);
U7Number* u7_number_new_from_bool (gboolean value);
U7Number* u7_number_construct_from_bool (GType object_type,
                                         gboolean value);
gint u7_number_as_int (U7Number* self);
gdouble u7_number_as_double (U7Number* self);
gboolean u7_number_as_bool (U7Number* self);
U7Number* u7_number_new (void);
U7Number* u7_number_construct (GType object_type);
U7NumberNumberType u7_number_get_number_type (U7Number* self);
GType u7_array_get_type (void) G_GNUC_CONST;
G_DEFINE_AUTOPTR_CLEANUP_FUNC (U7Array, g_object_unref)
U7Array* u7_array_new (GeeArrayList* value);
U7Array* u7_array_construct (GType object_type,
                             GeeArrayList* value);
GeeArrayList* u7_array_get_value (U7Array* self);
GType u7_thread_loop_get_type (void) G_GNUC_CONST;
G_DEFINE_AUTOPTR_CLEANUP_FUNC (U7ThreadLoop, g_object_unref)
extern gchar* u7_thread_loop_U7MainThreadName;
U7ThreadLoop* u7_thread_loop_mainThreadLoop (void);
void u7_thread_loop_threadEntry (U7ThreadLoop* self,
                                 U7PropertyList* info);
void u7_thread_loop_threadSetup (U7ThreadLoop* self);
GThread* u7_thread_loop_thread (U7ThreadLoop* self);
void u7_thread_loop_init (void);
U7ThreadLoop* u7_thread_loop_new (const gchar* name);
U7ThreadLoop* u7_thread_loop_construct (GType object_type,
                                        const gchar* name);
void u7_thread_loop_start (U7ThreadLoop* self);
const gchar* u7_thread_loop_get_name (U7ThreadLoop* self);
GType u7_keyboard_input_monitor_get_type (void) G_GNUC_CONST;
G_DEFINE_AUTOPTR_CLEANUP_FUNC (U7KeyboardInputMonitor, g_object_unref)
U7KeyboardInputMonitor* u7_keyboard_input_monitor_new (const gchar* name);
U7KeyboardInputMonitor* u7_keyboard_input_monitor_construct (GType object_type,
                                                             const gchar* name);
GType u7_dictionary_get_type (void) G_GNUC_CONST;
G_DEFINE_AUTOPTR_CLEANUP_FUNC (U7Dictionary, g_object_unref)
U7Dictionary* u7_dictionary_new (GeeHashMap* value);
U7Dictionary* u7_dictionary_construct (GType object_type,
                                       GeeHashMap* value);
GeeHashMap* u7_dictionary_get_value (U7Dictionary* self);
GType u7_date_get_type (void) G_GNUC_CONST;
G_DEFINE_AUTOPTR_CLEANUP_FUNC (U7Date, g_object_unref)
U7Date* u7_date_new (GDateTime* value);
U7Date* u7_date_construct (GType object_type,
                           GDateTime* value);
GDateTime* u7_date_get_value (U7Date* self);
GType u7_data_get_type (void) G_GNUC_CONST;
G_DEFINE_AUTOPTR_CLEANUP_FUNC (U7Data, g_object_unref)
U7Data* u7_data_new (GBytes* value);
U7Data* u7_data_construct (GType object_type,
                           GBytes* value);
GBytes* u7_data_get_value (U7Data* self);
U7PropertyList* u7_property_list_construct (GType object_type);
U7PropertyList* u7_property_list_deep_copy (U7PropertyList* self);
JsonNode* u7_property_list_to_json (U7PropertyList* self);
GQuark u7_error_quark (void);
U7PropertyList* u7_property_list_from_json (JsonNode* node,
                                            GError** error);
gchar* u7_property_list_to_json_string (U7PropertyList* self);
void u7_property_list_test_dictionary (void);
const gchar* u7_property_list_get_propertyType (U7PropertyList* self);

G_END_DECLS

#endif
