//#include <stdio.h>
#ifndef _AES_H
#define _AES_H

#ifdef __cplusplus
extern "C" {
#endif
#define Plain_Len_Max 4096  // 4*1024Bytes
#define Block_Size 16
#define err_plain_size 0xae01
void aes_enc(const char* plaintext, const char* key, char* ciphertext);
void aes_dec(const char* ciphertext, const char* key, char* plaintext);
int aes_encrypty(char* cipher, int* cipher_size, const char* plain,
                 int plain_size, const char* key, int key_size);
int aes_decrypty(char* plain, int* plain_size, const char* cipher,
                 int cipher_size, const char* key, int key_size);

int aes_encrypty_cbc(char* cipher, int* cipher_size, const char* plain,
                     int plain_size, const char* key, int key_size,
                     const char* IV, int IV_size);
int aes_decrypty_cbc(char* plain, int* plain_size, const char* cipher,
                     int cipher_size, const char* key, int key_size,
                     const char* IV, int IV_size);
#ifdef __cplusplus
}
#endif

#endif  //_AES_H