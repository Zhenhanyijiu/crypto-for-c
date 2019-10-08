#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <string>
#include "debug.h"

using namespace std;

int is_equal_arrary(const char* arr1, const char* arr2, int num) {
    if (arr1 == NULL || arr2 == NULL || num < 1) {
        return -2;
    }
    for (int i = 0; i < num; i++) {
        if ((char)arr2[i] != (char)arr2[i]) {
            return -1;
        }
    }
    return 0;
}

int copy_arrary(char* des, const char* src, int num) {
    if (des == NULL || src == NULL || num < 1) {
        return -2;
    }
    for (int i = 0; i < num; i++) {
        des[i] = src[i];
    }
    return 0;
}
// log——test
#if 0  // log-test
int main() {
    string out = "qiuxiaofang";
    string prefix = "test-log";
    char uchar_array[] = {(char)255, (char)254, (char)253, (char)252,
                          (char)127};
    LOG((char*)"you are %d years old,%s\n", 33, out.c_str());
    FLOG(stdout, (char*)"you are %d years old,%s\n", 33, out.c_str());
    LOGUCHAR(uchar_array, 5, prefix.c_str());
    FLOGUCHAR(stdout, uchar_array, 5, (char*)"");
}
#endif

#if 1  // aes-test
#include "aes.h"
int main() {
    unsigned int w[44];
    int i;
    unsigned char data[256] = {
        0xb1, 0xcd, 0x32, 0x27, 0x0d, 0xd0, 0x92, 0x12, 0xf5, 0x61, 0x31, 0x14,
        0x97, 0x62, 0x59, 0xc3, 0x37, 0xa2, 0x1e, 0x73, 0x89, 0x63, 0x45, 0x4d,
        0x11, 0x65, 0x2f, 0xb9, 0xb7, 0x91, 0x24, 0x2e, 0xb0, 0x47, 0x29, 0xb9,
        0xf4, 0x77, 0x5a, 0xd8, 0xfc, 0x44, 0x06, 0x35, 0x1d, 0x23, 0xf2, 0xcf};
    unsigned char keyt[16] = {0x0f, 0x15, 0x71, 0xc9, 0x47, 0xd9, 0xe8, 0x59,
                              0x0c, 0xb7, 0xad, 0xd6, 0xaf, 0x7f, 0x67, 0x98};
    // key_expansion(keyt, w);
    unsigned char plaint[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
                                0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10};
    unsigned char iv[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
                            0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10};

    unsigned char ciphert[16] = {0xff, 0x0b, 0x84, 0x4a, 0x08, 0x53,
                                 0xbf, 0x7c, 0x69, 0x34, 0xab, 0x43,
                                 0x64, 0x14, 0x8f, 0xb9};
    unsigned char cipher[256], plain[256];
    // // printf("enc: \n");
    // LOG((char*)"test aes_enc......\n");
    // aes_enc((char*)plain, (char*)keyt, (char*)cipher);
    // LOGUCHAR((char*)cipher, 16, (char*)"cipher by aes_enc");
    // LOGUCHAR((char*)ciphert, 16, (char*)"cipher           ");
    // // for (i = 0; i < 16; i++) {
    // //     printf("cipher[%d]: %x\n", i, cipher[i]);
    // // }
    // LOG((char*)"test aes_dec......\n");
    // aes_dec((char*)ciphert, (char*)keyt, (char*)plaint);
    // LOGUCHAR((char*)plaint, 16, (char*)"plain by aes_dec");
    // LOGUCHAR((char*)plain, 16, (char*)"plain           ");
    // printf("dec: \n");
    // for (i = 0; i < 16; i++) {
    //     printf("plaint[%d]: %x\n", i, plaint[i]);
    // }
    int fg = 77;
    // for (int i = 0; i < 10; i++) {
    //     // LOG((char*)"test aes_enc......\n");
    //     LOGUCHAR((char*)plain, 16, (char*)"plain ");
    //     aes_enc((char*)plain, (char*)keyt, (char*)cipher);
    //     LOGUCHAR((char*)cipher, 16, (char*)"cipher");
    //     // LOGUCHAR((char*)ciphert, 16, (char*)"cipher           ");
    //     // fg = is_equal_arrary((char*)cipher, (char*)ciphert, 16);

    //     // LOG((char*)"test aes_dec......\n");
    //     aes_dec((char*)cipher, (char*)keyt, (char*)plaint);
    //     // LOGUCHAR((char*)plaint, 16, (char*)"plain by aes_dec");
    //     // LOGUCHAR((char*)plain, 16, (char*)"plain           ");
    //     fg = is_equal_arrary((char*)plain, (char*)plaint, 16);
    //     if (fg != 0) {
    //         LOG((char*)"error error......\n");
    //         return -1;
    //     }
    //     copy_arrary((char*)plain, (char*)cipher, 16);
    // }
    int cipher_size = 0, plain_size = 0;
    for (int j = 0; j < 10; j++) {
        LOG((char*)"\n\n");
        for (int i = 1; i <= 48; i++) {
            // LOG((char*)"\n");
            aes_encrypty((char*)cipher, &cipher_size, (char*)data, i,
                         (char*)keyt, 16);
            LOGUCHAR((char*)cipher, cipher_size, "cipher");
            aes_decrypty((char*)plain, &plain_size, (char*)cipher, cipher_size,
                         (char*)keyt, 16);
            LOGUCHAR((char*)plain, plain_size, "plain ");
            fg = is_equal_arrary((char*)data, (char*)plain, plain_size);
            if (fg) {
                LOG((char*)"============eeeeeeerror==========\n\n");
                return 0;
            }
        }
    }
    LOG((char*)"================\n");
    LOG((char*)"================\n\n");
    for (int j = 0; j < 30000; j++) {
        LOG((char*)"\n\n");
        for (int i = 1; i <= 48; i++) {
            aes_encrypty_cbc((char*)cipher, &cipher_size, (char*)data, i,
                             (char*)keyt, 16, (char*)iv, 16);
            LOGUCHAR((char*)cipher, cipher_size, "cipher");
            aes_decrypty_cbc((char*)plain, &plain_size, (char*)cipher,
                             cipher_size, (char*)keyt, 16, (char*)iv, 16);
            LOGUCHAR((char*)plain, plain_size, "plain ");
            fg = is_equal_arrary((char*)data, (char*)plain, plain_size);
            if (fg) {
                LOG((char*)"============eeeeeeerror==========\n\n");
                return 0;
            }
        }
    }
}
#endif

#if 0  // base64
#include "base64.h"
void do_print() {
    LOG((char*)"{");
    for (int i = 65; i <= 90; i++) {
        /* code */
        LOG((char*)"\'%c\', ", (char)i);
    }
    for (int i = 97; i <= 122; i++) {
        /* code */
        LOG((char*)"\'%c\', ", (char)i);
    }
    for (int i = 48; i <= 57; i++) {
        /* code */
        LOG((char*)"\'%c\', ", (char)i);
    }
    LOG((char*)"\'%c\', ", (char)43);
    LOG((char*)"\'%c\'}\n", (char)47);
}
#define LEN 2
int main() {
    // Base64 basetest("SLFw");
    // Base64 basetest("U0xGdw==");
    // cout<<basetest.encode();
    // cout << basetest.decode();
    unsigned char input[] = {0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa1,
                             0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa1, 0xa2,
                             0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa1, 0xa2, 0xa3,
                             0xa4, 0xa5, 0xa6, 0xa7, 0xa3};  //(char*)"qiuxiaofang";
    char dst[12560] = {0};
    char ddst[12560] = {0};
    int num = 0;
    int fg = 7;
    // do_print();
    for (int i = 0; i < 10; i++) {
        fg = base64_encode(dst, &num, (char*)input, LEN);
        if (fg != 0) {
            LOG((char*)"eeeeeeeeeeeeerror ......\n");
            return -1;
        }
        LOG((char*)"%s, %d,num=%d,fg=%d\n", dst, (int)strlen(dst), num, fg);
        fg = base64_decode(ddst, &num, dst, num);
        if (fg != 0) {
            LOG((char*)"eeeeeeeeeeeeerror ......\n");
            return -1;
        }
        fg = is_equal_arrary(ddst, (char*)input, LEN);
        if (fg != 0) {
            LOG((char*)"eeeeeeeeeeeeerror ......\n");
            return -1;
        }
        LOG((char*)"num=%d,fg=%d\n", num, fg);
        LOGUCHAR(ddst, num, "");
    }
    LOG((char*)"======================\n\n");
    char tmp[12560] = {0};
    copy_arrary(tmp, (char*)input, LEN);
    int tmp_num = LEN;
    int num1 = 0;
    for (int i = 0; i < 20; i++) {
        LOG((char*)"index=%d\n\n", i);
        fg = base64_enc(dst, &num, (char*)tmp, tmp_num);
        if (fg != 0) {
            LOG((char*)"eeeeeeeeeeeeerror ......1,fg=%d\n", fg);
            return -1;
        }
        LOG((char*)"%s, %d,num=%d,fg=%d\n", dst, (int)strlen(dst), num, fg);
        fg = base64_dec(ddst, &num1, dst, num);
        if (fg != 0) {
            LOG((char*)"eeeeeeeeeeeeerror ......2,fg=%d\n", fg);
            return -1;
        }
        fg = is_equal_arrary(ddst, (char*)tmp, num1);
        if (fg != 0) {
            LOG((char*)"eeeeeeeeeeeeerror ......3,fg=%d\n", fg);
            return -1;
        }
        copy_arrary(tmp, dst, num);
        tmp_num = num;
        LOG((char*)"num=%d,fg=%d\n", num, fg);
        LOGUCHAR(ddst, num, "");
    }
    //  fg = base64_encode(dst, &num, (char*)input, 28);
    // LOG((char*)"%s, %d,num=%d,fg=%d\n", dst, (int)strlen(dst), num, fg);
    // fg = base64_decode(ddst, &num, dst, num);
    // LOG((char*)"num(-1)=%d\n", ('B' - 65));
    // LOGUCHAR(ddst, num, "");
    return 0;
}
#endif
#if 0
#include "rand.h"
int main() {
    for (int i = 0; i < 3; i++) {
        clock_t num = clock();
        LOG((char*)"%d\n", num);
    }
    char seed[16] = {0};
    char rand_num[16] = {0};
    int num = 0;
    // get_seed(seed, 16);
    // LOGUCHAR(seed, 16, "seed");
    // init_seed();
    init_seed();
    for (int i = 0; i < 100; i++) {
        rand_gen(rand_num, &num);
        LOGUCHAR(rand_num, 16, "seed");
        /* code */
    }
}
#endif