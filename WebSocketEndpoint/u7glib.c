#include "u7glib.h"

static char *global_info_prefix = NULL;
static int global_info_prefix_len = 0;

static GHashTable *hash_table = NULL;


char *j7_log_divider = "///////////////////////////////////////////////////////////////////////////";

// Helper function to handle variadic arguments and print to stderr
void U7ErrorHelper(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);  // Use vfprintf for va_list
    va_end(args);
}


double u7_time(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (double)tv.tv_usec / 1000000.0;
}






void u7glib_init(int argc, char *argv[], char *firstString, ...) {


    if (hash_table)
        return;

    u7_thread_main_init();
    hash_table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);

	char *key = NULL;
	for (int i = 0; i < argc; i++) {
		
        char *arg = argv[i];
        int arg_len = strlen(arg);

        if (arg_len < 1)
            continue;

		if (key) {
            if (arg_len) {
                g_hash_table_insert(hash_table, g_strdup(key), g_strdup(arg));
                printf("argv[] key/value pair found|%s=%s\n", key, arg);
            }
            key = NULL;
		} else {

            if (arg[0] == '-') {

                if ((arg_len > 1) && (arg[1] != '-') && (arg_len < 60)) {
                    key = &arg[1];
                }
            }
        }
	}

    char *prefix = g_hash_table_lookup(hash_table, "prefix");
    if (prefix == NULL) 
        prefix = "endpoint";

    global_info_prefix_len = strlen(prefix);
    if (global_info_prefix_len > 64) {
        printf("invalid global info steup prefix length\n");
        exit(-1);
    }

    global_info_prefix = malloc(global_info_prefix_len + 1);
    memcpy(global_info_prefix, prefix, global_info_prefix_len + 1);
    
    printf("prefix <%s>|len %i\n", prefix, global_info_prefix_len);

    if (firstString) {

        char env_key_buf[128];

        va_list argList;
        va_start(argList, firstString);
        char *string = firstString;
        char *key = NULL;

        do {
            
            int len = strlen(string);

            if (len < 1)
                continue;
            
            if (key) {

                if (string[0] != '-') {

                    char *lookup_value = g_hash_table_lookup(hash_table, key);

                    
                    char *env_val = NULL;
                    char *value = NULL;
                    sprintf(env_key_buf, "%s_%s", prefix, key);
                    env_val = getenv(env_key_buf);


                    if (env_val && strlen(env_val) < 1)
                        env_val = NULL;



                    gboolean replace_value = false;
                    if (!lookup_value) {

                        value = (env_val) ? env_val : string;
                        replace_value = (value != NULL);
                    } else {
                        value = lookup_value;
                        env_key_buf[0] = 0;
                    
                    }
                    
                    int password_compare = strcmp(key, "password");
                    if (password_compare == 0)
                        printf("%s=****|argv %p|env %p|default %p|", key, lookup_value, env_val, string);
                    else
                        printf("%s=%s|argv %s|env %s|default %s|", key, value, lookup_value, env_val, string);

                    if (replace_value) 
                        g_hash_table_insert(hash_table, g_strdup(key), g_strdup(value));

                    char *stored_value = (char *)g_hash_table_lookup(hash_table, key);
                    if (password_compare == 0)
                        printf("stored %p\n", stored_value);
                    else 
                        printf("stored %s\n", stored_value);

                }
                key = NULL;
            } else {
                if (string[0] == '-') {

                    if (len > 1) {

                        if (string[1] != '-') {

                            key = &string[1];

                        }
                    }
                }


            }



        } while((string = va_arg(argList, char *)));
        va_end(argList);

    }

    // printf("set_global_info_prefix() %s\n", global_info_prefix);

}

char *get_global_info_value(char *key) {

    if (key) {

        if (hash_table)
            return g_hash_table_lookup(hash_table, key);

    }

    return NULL;
}

int get_global_info_value_int(char *key) {

    char *value = get_global_info_value(key);
    if (value) {

        return atoi(value);

    }
    return 0;
}