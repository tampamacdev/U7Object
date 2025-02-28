
#include "u7encryption.h"


#include <openssl/evp.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

#define AES_KEYLEN 256
#define AES_BLOCK_SIZE 16
#define SALT_SIZE 8

#define DIVIDER_LENGTH 63
#define DIVIDER_BUFFER_LENGTH 64

void u7loghex(char *header, void *input, int len) {

    if (input == NULL)
        return;

	int blocks = len / 16;
	int rem = len % 16;
	unsigned char *ptr = input;
    char divider[DIVIDER_BUFFER_LENGTH];
    char info_buf[128];
    
    int lines = blocks / 4;
    if (blocks % 4)
        lines++;
    
    sprintf(info_buf, "len %i|lines %i|blocks %i|rem %i", len, lines, blocks, rem);

    int header_trim = strlen(header) + 16;
    int info_trim = strlen(info_buf) + 16;
    int divider_trim = (info_trim > header_trim) ? info_trim : header_trim;

    if (divider_trim > DIVIDER_LENGTH)
        divider_trim = DIVIDER_LENGTH;
    
    memset(divider, '/', divider_trim);

    divider[divider_trim] = 0;

    printf("%s\n////    %s\n////    %s\n%s\n", divider, header, info_buf, divider);
	for (int i = 0; i < blocks; i++) {
		printf("%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x", ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5], ptr[6], ptr[7], ptr[8], ptr[9], ptr[10], ptr[11], ptr[12], ptr[13], ptr[14], ptr[15]);
        if (i % 4 == 3)
            printf("\n");
        ptr += 16;
	}

    for (int i = 0; i < rem; i++) {
        printf("%02x", *ptr++);
    }
    
    if (blocks % 4 != 0)
        printf("\n");
	
}

gboolean derive_key_iv(const char *password, unsigned char *salt,
                   unsigned char *key, unsigned char *iv) {
    if (!EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha256(), salt,
                        (unsigned char *)password, strlen(password), 1, key, iv)) {
        return false;
    }
    return true;
}


char *u7_encrypt(char *input, int input_len, int *output_len_ptr, char *password) {
    return (char *)NULL;
}

char *u7_decrypt(char *input, int input_len, int *output_len_ptr, char *password) {
    return NULL;
}