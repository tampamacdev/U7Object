
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
    EVP_CIPHER_CTX *ctx = NULL;
    unsigned char salt[SALT_SIZE], key[AES_KEYLEN / 8], iv[AES_BLOCK_SIZE];
    int len, ciphertext_len;
    unsigned char *ciphertext = NULL;
    gboolean did_bail = FALSE;

    if (!(ciphertext = malloc(input_len + AES_BLOCK_SIZE + SALT_SIZE + 8))) {
        printf("Memory allocation for ciphertext failed\n");
        goto ERROR;
    }

    if (!RAND_bytes(salt, sizeof(salt))) {
        printf("Salt generation failed\n");
        goto ERROR;
    }

    if (derive_key_iv(password, salt, key, iv) == false) {
        printf("derive_key_iv() failed\n");
        goto ERROR;
    }

    if (!(ctx = EVP_CIPHER_CTX_new())) {
        printf("Encryption context creation failed\n");
        goto ERROR;
    }

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv) != 1) {
        printf("Encryption initialization failed\n");
        goto ERROR;
    }

    memcpy(ciphertext, "Salted__", 8);
    memcpy(ciphertext + 8, salt, SALT_SIZE);

    if (EVP_EncryptUpdate(ctx, ciphertext + SALT_SIZE + 8, &len, (unsigned char *)input, input_len) != 1) {
        printf("Encryption failed\n");
        goto ERROR;
    }
    ciphertext_len = len;

    if (EVP_EncryptFinal_ex(ctx, ciphertext + SALT_SIZE + 8 + len, &len) != 1) {
        printf("Final encryption step failed\n");
        goto ERROR;
    }
    ciphertext_len += len;

    *output_len_ptr = ciphertext_len + SALT_SIZE + 8;


ERROR:;

    if (did_bail) {
        if (ciphertext) {
            free(ciphertext);
            ciphertext = NULL;
        }
    }
    if (ctx) {
        EVP_CIPHER_CTX_free(ctx);
    }
    return (char *)ciphertext;
}

char *u7_decrypt(char *input, int input_len, int *output_len_ptr, char *password) {
    EVP_CIPHER_CTX *ctx = NULL;
    unsigned char key[AES_KEYLEN / 8], iv[AES_BLOCK_SIZE], salt[SALT_SIZE];
    int len, plaintext_len = 0;
    unsigned char *plaintext = NULL;
    gboolean did_bail = FALSE;

    if (input_len < 8 + SALT_SIZE || memcmp(input, "Salted__", 8) != 0) {
        printf("Invalid input\n");
        goto ERROR;
    }
    memcpy(salt, input + 8, SALT_SIZE);

    if (!(plaintext = malloc(input_len))) {
        printf("Memory allocation for plaintext failed\n");
        goto ERROR;
    }

    if (derive_key_iv(password, salt, key, iv) == false) {
        printf("derive_key_iv() failed\n");
        goto ERROR;
    }


    if (!(ctx = EVP_CIPHER_CTX_new())) {
        printf("Decryption context creation failed\n");
        goto ERROR;
    }

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv) != 1) {
        printf("Decryption initialization failed\n");
        goto ERROR;
    }

    if (EVP_DecryptUpdate(ctx, plaintext, &len, (unsigned char *)input + 16, input_len - 16) != 1) {
        printf("Decryption failed\n");
        goto ERROR;
    }
    plaintext_len = len;

    if (EVP_DecryptFinal_ex(ctx, plaintext + len, &len) != 1) {
        printf("Final decryption step failed\n");
        goto ERROR;
    }
    plaintext_len += len;

    *output_len_ptr = plaintext_len;

ERROR:;

    if (did_bail) {
        if (plaintext) {
            free(plaintext);
            plaintext = NULL;
        }
    }
    if (ctx) {
        EVP_CIPHER_CTX_free(ctx);
    }
    return (char *)plaintext;
}