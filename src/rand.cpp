#include <string.h>
#include <time.h>
#include "aes.h"
//#include "debug.h"
#define SEED_LEN 16
#define KEY_LEN 16
using namespace std;
static unsigned char SEED[] = {7, 7, 7, 7, 7, 7, 7, 7,
                               3, 3, 3, 3, 3, 3, 3, 3};  // initial seed
unsigned char KEY[KEY_LEN] = {0xac, 0x2e, 0xbc, 0x3f, 0x9e, 0x73, 0xb8, 0x3d,
                              0xa0, 0xdf, 0x71, 0xd1, 0xc2, 0xb6, 0xa4, 0xf3};
void get_seed(char *seed, int seed_len) {
    int count = (seed_len / 4) * 2;
    for (int i = 0; i < count; i++) {
        clock_t clock_value = clock();
        // LOG((char *)"%x\n", clock_value);
        memcpy(seed + 2 * i, &clock_value, 2);
        /* code */
    }
    // clock_t clock_value=clock();
}
void init_seed() {
    // LOGUCHAR((char *)SEED, SEED_LEN, "seed...1>>");
    get_seed((char *)SEED, SEED_LEN);
    // LOGUCHAR((char *)SEED, SEED_LEN, "seed...2>>");
}
void set_seed(char *seed, const char *src_sd, int seed_len) {
    memcpy(seed, src_sd, seed_len);
}
void rand_gen(char *rand_num, int *rand_size) {
    *rand_size = SEED_LEN;
    aes_enc((char *)SEED, (char *)KEY, rand_num);
    set_seed((char *)SEED, rand_num, SEED_LEN);
}