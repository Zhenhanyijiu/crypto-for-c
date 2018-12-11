#include <stdio.h>
void aes_enc(const char* plaintext, const unsigned char* key, char* ciphertext);
void aes_dec(const char* ciphertext, const unsigned char* key, char* plaintext);