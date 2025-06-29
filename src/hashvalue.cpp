#include "common.h"

int GetHashValue32(char* param_1);
int tHashName32_getHashValue(uint*, char*);

INCLUDE_ASM("hashvalue", tHashName32_getHashValue__FPUiPc);
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

INCLUDE_ASM("hashvalue", GetHashValue32__FPc);
#ifdef SKIP_ASM
int GetHashValue32(char* param_1) {
    char hash[4];
    return tHashName32_getHashValue((uint*)hash, param_1);
}
#endif

INCLUDE_ASM("hashvalue", GetHashValue64__FPc);
#ifdef SKIP_ASM
ulong tHashName64_getHashValue(ulong* out, char* str) {

    return (ulong)1;
}
#endif

INCLUDE_ASM("hashvalue", tHashName64_getHashValue__FPUlPc);
#ifdef SKIP_ASM
ulong GetHashValue64(char* str) {
    char hash[8];
    return tHashName64_getHashValue((ulong*)hash, str);
}
#endif