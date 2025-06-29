#include "common.h"

int GetHashValue32(char* param_1);
int tHashName32_getHashValue(uint*, char*);

INCLUDE_ASM("uncollated/HashValue32", tHashName32_getHashValue);
#ifdef SKIP_ASM
int tHashName32_getHashValue(uint* out, char* str) {
    uint hash = 0;
    uint top;

    while (*str) {
        hash = (hash << 4) + *str++;
        top = hash & 0xF0000000;
        if (top != 0) {
            hash = (hash ^ (top >> 23)) ^ top;
        }
    }

    *out = hash;
    return *out;
}
#endif

INCLUDE_ASM("uncollated/HashValue32", GetHashValue32);
#ifdef SKIP_ASM
int GetHashValue32(char* param_1) {
    char hash[4];
    return tHashName32_getHashValue((uint*)hash, param_1);
}
#endif