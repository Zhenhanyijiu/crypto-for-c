#include "log.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;
// static int N = 3;
int fprint(FILE* stream, char* format, ...) {
    va_list args;
    va_start(args, format);
    int fg = vfprintf(stream, format, args);
    va_end(args);
    // N = N + 7;
    // printf("N=%d\n", N);
    return fg;
}
int fprint_null(FILE* stream, char* format, ...) { return 0; }

int print(char* format, ...) {
    va_list args;
    va_start(args, format);
    int fg = vprintf(format, args);
    va_end(args);
    return fg;
}
int print_null(char* format, ...) {}

int fprint_uchar_array(FILE* stream, const char* array, int size,
                       const char* prefix) {
    if (stream == NULL || array == NULL || size < 1) {
        // return NULL
        return -1;
    }
    // string fmt = "%s: {";

    if (strlen(prefix) == 0) {
        // fmt = "%s{";
        fprint(stream, (char*)"%s{", prefix);
    } else {
        fprint(stream, (char*)"%s: {", prefix);
    }

    for (int i = 0; i < size; i++) {
        /* code */
        if ((unsigned char)array[i] < 0x10) {
            if (i == size - 1) {
                fprint(stream, (char*)"0x0%x", (unsigned char)array[i]);
                break;
            }
            fprint(stream, (char*)"0x0%x, ", (unsigned char)array[i]);
        } else {
            if (i == size - 1) {
                fprint(stream, (char*)"0x%x", (unsigned char)array[i]);
                break;
            }
            fprint(stream, (char*)"0x%x, ", (unsigned char)array[i]);
        }
        // if (i == size - 1) {
        //     fprint(stream, (char*)"0x%x", (unsigned char)array[i]);
        //     break;
        // }
        // fprint(stream, (char*)"0x%x, ", (unsigned char)array[i]);
    }
    fprint(stream, (char*)"}, length=%d\n", size);
    return 0;

    //     fprint() va_list args;
    // va_start(args, format);
    // vfprintf(stream, format, args);
    // va_end(args);
}
int print_uchar_array(const char* array, int size, const char* prefix) {
    if (array == NULL || size < 1) {
        // return NULL
        return -1;
    }
    // string fmt = "%s: {";

    if (strlen(prefix) == 0) {
        // fmt = "%s{";
        print((char*)"%s{", prefix);
    } else {
        print((char*)"%s: {", prefix);
    }

    for (int i = 0; i < size; i++) {
        /* code */
        if ((unsigned char)array[i] < 0x10) {
            if (i == size - 1) {
                print((char*)"0x0%x", (unsigned char)array[i]);
                break;
            }
            print((char*)"0x0%x, ", (unsigned char)array[i]);
        } else {
            if (i == size - 1) {
                print((char*)"0x%x", (unsigned char)array[i]);
                break;
            }
            print((char*)"0x%x, ", (unsigned char)array[i]);
        }
    }
    print((char*)"}, lengrh=%d\n", size);

    return 0;
}
int fprint_null_uchar_array(FILE* stream, const char* array, int size,
                            const char* prefix) {
    return 0;
}
int print_null_uchar_array(const char* array, int size, const char* prefix) {
    return 0;
}