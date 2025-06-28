#include "common.h"
int GetHashValue32(char* param_1);
int tHashName32_scoperes_getHashValue(int*, char*);

INCLUDE_ASM("uncollated/HashValue32", tHashName32_getHashValue);
int tHashName32_scoperes_getHashValue(int* out, char* str) {
    int hash = 0;
    int top = 0;

    while (*str) {
        hash = (hash << 4) + (signed char)(*str++);
        top = hash & 0xF0000000;
        if (top != 0) {
            hash ^= (top >> 23);
            hash ^= top;
        }
    }

    *out = hash;
    return hash;
}


INCLUDE_ASM("uncollated/HashValue32", GetHashValue32);
int GetHashValue32(char* param_1) {
    char hash[4];
    return tHashName32_scoperes_getHashValue((int*)hash, param_1);
}