#include "common.h"

extern int D_005305B0[];

struct sCharEntry {
    char pad_0x00[0x11];
    signed char mCharID; // 0x11
    char pad_0x12[0x1C - 0x11 - 1];
};
extern sCharEntry D_00535B20[];

//100%
INCLUDE_ASM("be/belibrary", cBELibrary_getCharacterID__Fi);
#ifdef SKIP_ASM
signed char cBELibrary_getCharacterID(int index)
{
    int charID = D_005305B0[index];
    sCharEntry* entry = &D_00535B20[charID];
    return entry->mCharID;
}
#endif

INCLUDE_ASM("be/belibrary", func_0014A0B0);

struct sCharEntry2 {
    char pad_0x00[0xC];
    int field_0xC;
    int field_0x10;
};

//100%
INCLUDE_ASM("be/belibrary", cBELibrary_getProfileIndex__Fi);
#ifdef SKIP_ASM
int cBELibrary_getProfileIndex(int index)
{
    int charID = D_005305B0[index];
    sCharEntry2* entry = (sCharEntry2*)((char*)D_00535B20 + charID * 0x1C);
    if (entry->field_0xC == -1) {
        return 2;
    }
    return entry->field_0x10 & 1;
}
#endif

//100%
INCLUDE_ASM("be/belibrary", cBELibrary_getRiderIndex__Fi);
#ifdef SKIP_ASM
int cBELibrary_getRiderIndex(int flag)
{
    int* base = D_005305B0;
    int count = 0;
    while (1) {
        int charID = *base;
        sCharEntry2* entry = (sCharEntry2*)((char*)D_00535B20 + charID * 0x1C);
        int bit = entry->field_0x10 & 1;
        if (bit == flag) {
            return count;
        }
        count++;
        if (count < 6) {
            base++;
            continue;
        }
        return -1;
    }
}
#endif

INCLUDE_ASM("be/belibrary", func_0014A188);

INCLUDE_ASM("be/belibrary", func_0014A5E0);

INCLUDE_ASM("be/belibrary", func_0014AB20);

INCLUDE_ASM("be/belibrary", cBELibrary_getScoreType);

INCLUDE_ASM("be/belibrary", func_0014ABE0);

INCLUDE_ASM("be/belibrary", func_0014AC30);

INCLUDE_ASM("be/belibrary", func_0014AC50);

INCLUDE_ASM("be/belibrary", func_0014ACB0);

INCLUDE_ASM("be/belibrary", func_0014AD28);

INCLUDE_ASM("be/belibrary", func_0014AD50);

INCLUDE_ASM("be/belibrary", func_0014AEA8);

INCLUDE_ASM("be/belibrary", func_0014AF10);

INCLUDE_ASM("be/belibrary", func_0014AFB0);

INCLUDE_ASM("be/belibrary", func_0014B478);

INCLUDE_ASM("be/belibrary", func_0014B560);

INCLUDE_ASM("be/belibrary", func_0014B700);

INCLUDE_ASM("be/belibrary", func_0014B988);

extern void* D_004A6750[];
extern "C" void* func_0014C6A0(void*);

//100%
INCLUDE_ASM("be/belibrary", func_0014BD78__FPv);
#ifdef SKIP_ASM
void* func_0014BD78(void* self)
{
    return func_0014C6A0((void*)D_004A6750);
}
#endif

extern "C" void* func_0014D068(void*);

//100%
INCLUDE_ASM("be/belibrary", func_0014BD98__FPv);
#ifdef SKIP_ASM
void* func_0014BD98(void* self)
{
    return func_0014D068((void*)D_004A6750);
}
#endif

//100%
INCLUDE_ASM("be/belibrary", func_0014BDB8__FPv);
#ifdef SKIP_ASM
void* func_0014BDB8(void* self)
{
    return (void*)D_004A6750;
}
#endif

INCLUDE_ASM("be/belibrary", func_0014BE70);

INCLUDE_ASM("be/belibrary", func_0014C2B0);

INCLUDE_ASM("be/belibrary", func_0014C320);

INCLUDE_ASM("be/belibrary", func_0014C3C8);

INCLUDE_ASM("be/belibrary", func_0014C488);

INCLUDE_ASM("be/belibrary", func_0014C620);

INCLUDE_ASM("be/belibrary", func_0014C658);

INCLUDE_ASM("be/belibrary", func_0014C6A0);

INCLUDE_ASM("be/belibrary", func_0014C7A0);

INCLUDE_ASM("be/belibrary", func_0014D068);

INCLUDE_ASM("be/belibrary", func_0014D240);

INCLUDE_ASM("be/belibrary", func_0014D448);

INCLUDE_ASM("be/belibrary", func_0014D4C8);

INCLUDE_ASM("be/belibrary", func_0014D558);

INCLUDE_ASM("be/belibrary", func_0014D608);

INCLUDE_ASM("be/belibrary", func_0014D7E8);

INCLUDE_ASM("be/belibrary", func_0014D908);

//95.0%
INCLUDE_ASM("be/belibrary", func_0014D988__FPvi);
#ifdef SKIP_ASM
int func_0014D988(void* self, int a1)
{
    return *(int*)((char*)((char*)self + a1 * 4) + 0x2c);
}
#endif

INCLUDE_ASM("be/belibrary", func_0014D998);

INCLUDE_ASM("be/belibrary", func_0014D9D0);

INCLUDE_ASM("be/belibrary", func_0014DB40);

//95.0%
INCLUDE_ASM("be/belibrary", func_0014DC00__FPvi);
#ifdef SKIP_ASM
int func_0014DC00(void* self, int a1)
{
    return *(int*)((char*)((char*)self + a1 * 4) + 0x2fc);
}
#endif

INCLUDE_ASM("be/belibrary", func_0014DC10);

//95.0%
INCLUDE_ASM("be/belibrary", func_0014DC40__FPvi);
#ifdef SKIP_ASM
int func_0014DC40(void* self, int a1)
{
    return *(int*)((char*)((char*)self + a1 * 4) + 0x3ec);
}
#endif

INCLUDE_ASM("be/belibrary", func_0014DC50);

