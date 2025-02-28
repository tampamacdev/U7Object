

#ifndef U7_HASHTABLE_H
#define U7_HASHTABLE_H

#include <glib.h>
#include <stdint.h>

extern char *u7_process_c_string(char *str);
extern int u7_process_int(int value);
extern double u7_process_double(double val);
extern void *u7_process_u7_string(void *string);
extern void *u7_process_g_object(void *obj);
extern void u7_tls_set_thread_uint64_id(uint64_t val);
extern uint64_t u7_tls_get_thread_uint64_id();

typedef struct _U7HashTable U7HashTable;

// Create a new hash table
U7HashTable* u7_hashtable_new();

// Destroy the hash table and free its resources
void u7_hashtable_destroy(U7HashTable* table);

// Insert or update a key-value pair (takes ownership of value)
void u7_hashtable_set(U7HashTable* table, uint64_t key, void *value);
// Get the value associated with a key (returns NULL if not found)
void* u7_hashtable_get(U7HashTable* table, uint64_t key);
guint64 *u7_uint64(guint64 val);
#endif


