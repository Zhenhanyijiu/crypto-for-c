#ifndef _BASE64_H
#define _BASE64_H

// #ifdef __cplusplus
// extern "C" {
// #endif
//#include "debug.h"
#define err_param 0xb1
#define err_not_base64 0xb2
// cpp language
int base64_encode(char* dest, int* dest_size, const char* src, int src_size);
int base64_decode(char* dest, int* dest_size, const char* src, int src_size);
// c language
int base64_enc(char* dest, int* dest_size, const char* src, int src_size);
int base64_dec(char* dest, int* dest_size, const char* src, int src_size);

// #ifdef __cplusplus
// }
// #endif

#endif  //_BASE64_H