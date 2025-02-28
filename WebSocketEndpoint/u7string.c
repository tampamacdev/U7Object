#include "u7string.h"

struct _U7String {
    U7Object parent_instance;
    char *buffer;
};

struct _U7StringClass {
    U7ObjectClass parent_class;
};

G_DEFINE_TYPE(U7String, u7_string, U7_TYPE_OBJECT)

static void u7_string_dispose(GObject *object) {

    U7String *string = U7_STRING(object);
    if (string) {
        if (string->buffer) {
            free(string->buffer);
            string->buffer = NULL;
        }
    }

    G_OBJECT_CLASS(u7_string_parent_class)->dispose(object);

}

static char *u7_string_description(U7Object *obj) {
    if (U7IsString(obj)) 
        return u7_string_getCString(U7_STRING(obj));
    return NULL;
}

static void u7_string_class_init(U7StringClass *klass) {
    // Class initialization logic, if needed
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->dispose = u7_string_dispose;

    U7ObjectClass *u7_object_class = U7_OBJECT_CLASS(klass);
    u7_object_class->description = u7_string_description;

}

static void u7_string_init(U7String *self) {

    //printf("u7_string_init\n");

}

U7String *u7_string_new(char *str) {
    U7String *self = g_object_new(U7_TYPE_STRING, NULL);
    if (str) {

        int len = strlen(str);
        if (len < 65536) {
            self->buffer = malloc(len + 1);
            memcpy(self->buffer, str, len);
            self->buffer[len] = 0;
        }
        //printf("u7_string_new()|len %i|string %s\n", len, U7Str(self));

    }
    return self;
}

char *u7_string_getCString(U7String *string) {
    if (U7IsString(string))
        return (string->buffer) ? string->buffer : "(U7String with no buffer)";
    return "invalid";
}

void u7_string_test(void) {

    U7String *string = u7_string_new("test string");
    
    printf("u7_string_test()|string %s\n", U7Str(string));

    U7Release(string);

}



///////////////////////////////////////////////////////

gboolean u7_cstrings_are_equal(const char *str1, int str1_len, const char *trimmed_str2, int str2_len) {
    gboolean are_equal = false;
    int leading_gap = 0, trailing_gap = 0;

    if (str1 && trimmed_str2) {
        if (str1_len >= str2_len) {
            char *result = g_ascii_strdown((gchar *)str1, str1_len);
            char *cmp_str = g_ascii_strdown((gchar *)trimmed_str2, str2_len);
            char *found = strstr(result, cmp_str);

            if (found) {
                leading_gap = found - result;
                trailing_gap = str1_len - leading_gap - str2_len;

                if ((leading_gap + str2_len + trailing_gap) == str1_len) {
                    for (int i = 0; i < leading_gap; i++) {
                        if (!isspace((unsigned char)str1[i])) {
                            g_free(result);
                            g_free(cmp_str);
                            return false;
                        }
                    }

                    for (int i = str2_len + leading_gap; i < str1_len; i++) {
                        if (!isspace((unsigned char)str1[i])) {
                            g_free(result);
                            g_free(cmp_str);
                            return false;
                        }
                    }

                    are_equal = true;
                }
            }
            g_free(result);
            g_free(cmp_str);
        }
    }

    return are_equal;
}

char *u7_hms(char *buf, double time) {

    
    time = fabs(time);
    double f_sec = floor(time);
    double f_rem = time - f_sec;
    int sec = lrint(f_sec);
    int min = sec / 60;
    sec -= min * 60;
    int hr = min / 60;
    min -= hr * 60;
    double f_milli = f_rem * 1000.0f;
    sprintf(buf, "%02i:%02i:%02i.%03li", hr, min, sec, lrint(floor(f_milli)));

    return buf;
}

char *u7_timestamp_create(void) {
    // Get current time as GDateTime
    GDateTime *dt = g_date_time_new_now_local(); // Local time, or use g_date_time_new_now_utc() for UTC
    
    // Format it into a human-readable string
    char *timestamp = g_date_time_format(dt, "%Y-%m-%d %H:%M:%S");
    // Example output: "2025-02-18 15:27:45" (assuming current time in EST adjusted to local)

    // Clean up GDateTime
    g_date_time_unref(dt);

    // The returned string is newly allocated and must be freed with g_free()
    return timestamp;
}
