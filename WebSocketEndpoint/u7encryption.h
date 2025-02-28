#include "u7glib.h"



extern char *u7_encrypt(char *input, int input_len, int *output_len_ptr, char *password);
extern char *u7_decrypt(char *input, int input_len, int *output_len_ptr, char *password);
extern void u7loghex(char *header, void *input, int len);