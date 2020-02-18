#include "base64.h"
#include <stdio.h>
#include <string.h>
#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;
map<unsigned short, char> Base64Table{
    {0, 'A'},  {1, 'B'},  {2, 'C'},  {3, 'D'},  {4, 'E'},  {5, 'F'},  {6, 'G'},
    {7, 'H'},  {8, 'I'},  {9, 'J'},  {10, 'K'}, {11, 'L'}, {12, 'M'}, {13, 'N'},
    {14, 'O'}, {15, 'P'}, {16, 'Q'}, {17, 'R'}, {18, 'S'}, {19, 'T'}, {20, 'U'},
    {21, 'V'}, {22, 'W'}, {23, 'X'}, {24, 'Y'}, {25, 'Z'}, {26, 'a'}, {27, 'b'},
    {28, 'c'}, {29, 'd'}, {30, 'e'}, {31, 'f'}, {32, 'g'}, {33, 'h'}, {34, 'i'},
    {35, 'j'}, {36, 'k'}, {37, 'l'}, {38, 'm'}, {39, 'n'}, {40, 'o'}, {41, 'p'},
    {42, 'q'}, {43, 'r'}, {44, 's'}, {45, 't'}, {46, 'u'}, {47, 'v'}, {48, 'w'},
    {49, 'x'}, {50, 'y'}, {51, 'z'}, {52, '0'}, {53, '1'}, {54, '2'}, {55, '3'},
    {56, '4'}, {57, '5'}, {58, '6'}, {59, '7'}, {60, '8'}, {61, '9'}, {62, '+'},
    {63, '/'},

};

map<char, unsigned short> RevTb{
    {'A', 0},  {'B', 1},  {'C', 2},  {'D', 3},  {'E', 4},  {'F', 5},  {'G', 6},
    {'H', 7},  {'I', 8},  {'J', 9},  {'K', 10}, {'L', 11}, {'M', 12}, {'N', 13},
    {'O', 14}, {'P', 15}, {'Q', 16}, {'R', 17}, {'S', 18}, {'T', 19}, {'U', 20},
    {'V', 21}, {'W', 22}, {'X', 23}, {'Y', 24}, {'Z', 25}, {'a', 26}, {'b', 27},
    {'c', 28}, {'d', 29}, {'e', 30}, {'f', 31}, {'g', 32}, {'h', 33}, {'i', 34},
    {'j', 35}, {'k', 36}, {'l', 37}, {'m', 38}, {'n', 39}, {'o', 40}, {'p', 41},
    {'q', 42}, {'r', 43}, {'s', 44}, {'t', 45}, {'u', 46}, {'v', 47}, {'w', 48},
    {'x', 49}, {'y', 50}, {'z', 51}, {'0', 52}, {'1', 53}, {'2', 54}, {'3', 55},
    {'4', 56}, {'5', 57}, {'6', 58}, {'7', 59}, {'8', 60}, {'9', 61}, {'+', 62},
    {'/', 63},

};

class Base64 {
   public:
    vector<char> vch;
    Base64() {}
    Base64(const vector<char>& vc) { vch = vc; }
    Base64(const string& str) {
        assert(!str.empty());
        for (unsigned int i = 0; i < str.size(); i++) {
            vch.push_back(str.at(i));
        }
    }
    Base64(const char* str, int size) {
        // assert(!str.empty());
        // assert(strlen(str) != 0);
        assert(size > 0);
        for (unsigned int i = 0; i < size; i++) {
            vch.push_back(str[i]);
        }
    }
    string encode() {
        unsigned int q, r, nsize;
        string strret = "";
        nsize = vch.size();
        q = nsize / 3;
        r = nsize % 3;
        unsigned short tmp;
        for (unsigned int i = 0; i < q; i++)  // 3*i,3*i+1,3*i+2
        {
            auto it = vch.begin() + 3 * i;
            tmp = ((*(it)) >> 2) & 0x3f;
            strret.push_back(Base64Table[tmp]);
            tmp = ((*(it)&0x03) << 4) | ((*(it + 1) >> 4) & 0x0f);
            strret.push_back(Base64Table[tmp]);
            tmp = ((*(it + 1) & 0x0f) << 2) | ((*(it + 2) >> 6) & 0x03);
            strret.push_back(Base64Table[tmp]);
            tmp = ((*(it + 2))) & 0x3f;
            strret.push_back(Base64Table[tmp]);
        }
        auto it = vch.begin() + 3 * q;
        if (r == 1) {
            tmp = (*(it) >> 2) & 0x3f;
            strret.push_back(Base64Table[tmp]);
            tmp = (*(it)&0x03) << 4;
            strret.push_back(Base64Table[tmp]);
            strret.push_back('=');
            strret.push_back('=');
        }
        if (r == 2) {
            tmp = ((*(it)) >> 2) & 0x3f;
            strret.push_back(Base64Table[tmp]);
            tmp = ((*(it)&0x03) << 4) | ((*(it + 1) >> 4) & 0x0f);
            strret.push_back(Base64Table[tmp]);
            tmp = (*(it + 1) & 0x0f) << 2;
            strret.push_back(Base64Table[tmp]);
            strret.push_back('=');
        }
        return strret;
    }

    string decode() {
        unsigned int q, nsize;
        string strret = "";
        nsize = vch.size();
        q = nsize / 4;
        // r = nsize % 3;
        unsigned short tmp;
        for (unsigned int i = 0; i < q; i++)  // 4*i,4*i+1,4*i+2,4*i+3
        {
            auto it = vch.begin() + 4 * i;
            if (*(it + 2) != '=' && *(it + 3) != '=') {
                tmp = ((RevTb[*(it)] & 0x3f) << 2) |
                      ((RevTb[*(it + 1)] >> 4) & 0x03);
                strret.push_back((char)tmp);
                tmp = ((RevTb[*(it + 1)] & 0x0f) << 4) |
                      ((RevTb[*(it + 2)] >> 2) & 0x0f);
                strret.push_back((char)tmp);
                tmp = ((RevTb[*(it + 2)] & 0x03) << 6) |
                      (RevTb[*(it + 3)] & 0x03f);
                strret.push_back((char)tmp);
            } else if (*(it + 2) != '=') {
                tmp = ((RevTb[*(it)] & 0x3f) << 2) |
                      ((RevTb[*(it + 1)] >> 4) & 0x03);
                strret.push_back((char)tmp);
                tmp = ((RevTb[*(it + 1)] & 0x0f) << 4) |
                      ((RevTb[*(it + 2)] >> 2) & 0x0f);
                strret.push_back((char)tmp);
            } else {
                tmp = ((RevTb[*(it)] & 0x3f) << 2) |
                      ((RevTb[*(it + 1)] >> 4) & 0x03);
                strret.push_back((char)tmp);
            }
            // tmp = (*(it + 2)) & 0x3f;
            // strret.push_back(Base64Table[tmp]);
        }
        return strret;
    }
};

int base64_encode(char* dest, int* dest_size, const char* src, int src_size) {
    if (src == NULL || src_size < 1 || dest == NULL || dest_size == NULL) {
        return err_param;
    }
    Base64 enc = Base64(src, src_size);
    string res = enc.encode();
    const char* cstr = res.c_str();
    int cstr_size = strlen(cstr);
    *dest_size = cstr_size;
    // if (dest_size)
    // dest[dest_size]
    // strcpy();
    // LOG((char*)"=====%s, %d,num=%d\n", cstr, (int)strlen(cstr), cstr_size);
    memcpy(dest, cstr, cstr_size);

    return 0;
}
int base64_decode(char* dest, int* dest_size, const char* src, int src_size) {
    if (src == NULL || src_size < 1 || dest == NULL || dest_size == NULL) {
        return err_param;
    }
    Base64 dec = Base64(src, src_size);
    string res = dec.decode();
    const char* cstr = res.c_str();
    int cstr_size = strlen(cstr);
    *dest_size = cstr_size;
    // if (dest_size)
    // dest[dest_size]
    // strcpy();
    // const char* cstr = res.c_str();
    // printf("=====%s, %d,num=%d\n", cstr, (int)strlen(cstr), cstr_size);
    // cout << cstr;
    memcpy(dest, cstr, cstr_size);
    return 0;
}
/*
A-----Z, a--------z, 0------9, +   /
65---90, 97-----122, 48----57, 43 47
*/
char reverse_base64_table(char c) {
    if (c >= 65 && c <= 90) {
        return (char)(c - 65);
    }
    if (c >= 97 && c <= 122) {  //-97+26
        return (char)(c - 71);
    }
    if (c >= 48 && c <= 57) {  //-48+52
        return (char)(c + 4);
    }
    if (c == 43) {
        return (char)62;
    }
    if (c == 47) {
        return (char)63;
    }
    // if (c == '=') {
    //     return (char)63;
    // }
    return -1;
}
char base64_table[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                         'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                         'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                         'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                         's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2',
                         '3', '4', '5', '6', '7', '8', '9', '+', '/'};
// C语言版
int base64_enc(char* dest, int* dest_size, const char* src, int src_size) {
    if (src == NULL || src_size < 1 || dest == NULL || dest_size == NULL) {
        return err_param;
    }
    int times_3 = src_size / 3;
    int remain = src_size % 3;
    int count = 0;
    int j, k;
    unsigned char tmp;
    for (int i = 0; i < times_3; i++) {
        /* code */
        // for (int j = 4 * i; j < 4 * i + 4; j++) {
        // }
        j = 4 * i;
        k = 3 * i;
        tmp = (src[k] >> 2) & 0x3f;
        dest[j] = base64_table[tmp];
        tmp = ((src[k] & 0x3) << 4) | ((src[k + 1] >> 4) & 0xf);
        dest[j + 1] = base64_table[tmp];
        tmp = ((src[k + 1] & 0xf) << 2) | ((src[k + 2] >> 6) & 0x3);
        dest[j + 2] = base64_table[tmp];
        tmp = src[k + 2] & 0x3f;
        dest[j + 3] = base64_table[tmp];
    }
    count = times_3 * 4;
    if (remain == 0) {
        *dest_size = count;
        return 0;
    }
    k = 3 * times_3;
    tmp = (src[k] >> 2) & 0x3f;
    dest[count] = base64_table[tmp];
    if (remain == 1) {
        // k = 3 * times_3;
        // tmp = (src[k] >> 2) & 0x3f;
        // dest[count] = base64_table[tmp];
        tmp = (src[k] & 0x3) << 4;
        dest[count + 1] = base64_table[tmp];
        dest[count + 2] = '=';
        dest[count + 3] = '=';
        count += 4;
    }
    if (remain == 2) {
        // k = 3 * times_3;
        // tmp = (src[k] >> 2) & 0x3f;
        // dest[count] = base64_table[tmp];
        tmp = ((src[k] & 0x3) << 4) | ((src[k + 1] >> 4) & 0xf);
        dest[count + 1] = base64_table[tmp];
        tmp = ((src[k + 1] & 0xf) << 2);  // | ((src[k + 2] >> 6) & 0x3);
        dest[count + 2] = base64_table[tmp];
        dest[count + 3] = '=';
        count += 4;
    }
    *dest_size = count;
    return 0;
}

int base64_dec(char* dest, int* dest_size, const char* src, int src_size) {
    if (src == NULL || src_size < 1 || dest == NULL || dest_size == NULL ||
        src_size % 4 != 0) {
        return err_param;
    }
    int times_4 = src_size / 4;
    // int remain = src_size % 3;
    int count = 0;
    int j, k;
    char s0, s1, s2, s3;
    char src_end = src[src_size - 1];
    for (int i = 0; i < times_4 - 1; i++) {
        /* code */
        j = 4 * i;
        k = 3 * i;
        s0 = reverse_base64_table(src[j]);
        s1 = reverse_base64_table(src[j + 1]);
        s2 = reverse_base64_table(src[j + 2]);
        s3 = reverse_base64_table(src[j + 3]);
        if ((s0 == (char)(-1)) || (s1 == (char)(-1)) || (s2 == (char)(-1)) ||
            (s3 == (char)(-1))) {
            return err_not_base64;
        }
        // if (i < times_4 - 1 || src_end != '=') {
        dest[k] = s0 << 2 | ((s1 >> 4) & 0x3);
        dest[k + 1] = ((s1 & 0xf) << 4) | ((s2 >> 2) & 0xf);
        dest[k + 2] = ((s2 & 0x3) << 6) | (s3 & 0x3f);
        //}
    }
    count = 3 * (times_4 - 1);
    j = 4 * (times_4 - 1);
    s0 = reverse_base64_table(src[j]);
    s1 = reverse_base64_table(src[j + 1]);
    if ((s0 == (char)(-1)) || (s1 == (char)(-1))) {
        return err_not_base64;
    }
    // s2 = reverse_base64_table(src[j + 2]);
    // s3 = reverse_base64_table(src[j + 3]);
    dest[count] = s0 << 2 | (s1 >> 4 & 0x3);
    if (src[j + 2] == '=') {
        // dest[count] = s0 << 2 | (s1 >> 4 & 0x3);
        *dest_size = count + 1;
        return 0;
    }
    s2 = reverse_base64_table(src[j + 2]);
    if ((s2 == (char)(-1))) {
        return err_not_base64;
    }
    dest[count + 1] = ((s1 & 0xf) << 4) | ((s2 >> 2) & 0xf);
    if (src[j + 3] == '=') {
        // s2 = reverse_base64_table(src[j + 2]);
        // dest[count] = s0 << 2 | (s1 >> 4 & 0x3);
        // dest[count + 1] = ((s1 & 0xf) << 4) | ((s2 >> 2) & 0xf);
        *dest_size = count + 2;
        return 0;
    }
    // s2 = reverse_base64_table(src[j + 2]);
    s3 = reverse_base64_table(src[j + 3]);
    if ((s3 == (char)(-1))) {
        return err_not_base64;
    }
    // dest[count] = s0 << 2 | ((s1 >> 4) & 0x3);
    // dest[count + 1] = ((s1 & 0xf) << 4) | ((s2 >> 2) & 0xf);
    dest[count + 2] = ((s2 & 0x3) << 6) | (s3 & 0x3f);
    *dest_size = count + 3;
    return 0;
}
