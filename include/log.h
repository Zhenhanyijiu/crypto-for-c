#ifndef _LOG_H
#define _LOG_H
#ifdef __cplusplus
//#include <string>
// using namespace std;
extern "C" {
#endif
#include <stdarg.h>
#include <stdio.h>

int fprint_null(FILE* stream, char* format, ...);
int fprint(FILE* stream, char* format, ...);
int print_null(char* format, ...);
int print(char* format, ...);
////
int fprint_uchar_array(FILE* stream, const char* array, int size,
                       const char* prefix);
int print_uchar_array(const char* array, int size, const char* prefix);
int fprint_null_uchar_array(FILE* stream, const char* array, int size,
                            const char* prefix);
int print_null_uchar_array(const char* array, int size, const char* prefix);
#ifdef __cplusplus
}
#endif
#endif  //_LOG_H