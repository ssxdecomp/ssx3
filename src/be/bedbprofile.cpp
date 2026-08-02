#include "common.h"

extern "C" int cBELibrary_getScoreType(int a, int b);

//93.68%
INCLUDE_ASM("be/bedbprofile", cBECharProfileDB_getScoreStats__FPvii);
#ifdef SKIP_ASM
void* cBECharProfileDB_getScoreStats(void* self, int a, int b)
{
    int type = cBELibrary_getScoreType(a, b);
    if (type == 0x1A) {
        return 0;
    }
    return (char*)self + (type << 3) + 0xAD0;
}
#endif

INCLUDE_ASM("be/bedbprofile", func_001523E8);

INCLUDE_ASM("be/bedbprofile", func_00152430);

INCLUDE_ASM("be/bedbprofile", func_00152460);

INCLUDE_ASM("be/bedbprofile", func_00152528);

