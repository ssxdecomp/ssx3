#include "common.h"

INCLUDE_ASM("fe/fereal", cFECustom_cFECustom);

INCLUDE_ASM("fe/fereal", func_001A07C8);

INCLUDE_ASM("fe/fereal", cFECustom_getNextState);

INCLUDE_ASM("fe/fereal", func_001A16C0);

//100%
INCLUDE_ASM("fe/fereal", func_001A1CB8);
#ifdef SKIP_ASM
extern "C" void func_001A1CB8(void* self, int a1, int val)
{
    char* p = (char*)self + (signed char)a1;
    *(char*)(p + 0x8) = val;
}
#endif

//100%
INCLUDE_ASM("fe/fereal", func_001A1CD0);
#ifdef SKIP_ASM
extern "C" unsigned char func_001A1CD0(void* self, int a1)
{
    char* p = (char*)self + (signed char)a1;
    return *(unsigned char*)(p + 0x8);
}
#endif

INCLUDE_ASM("fe/fereal", func_001A1CE8);

INCLUDE_ASM("fe/fereal", func_001A1D50);

INCLUDE_ASM("fe/fereal", func_001A1DC0);

INCLUDE_ASM("fe/fereal", cRealFE_load);

INCLUDE_ASM("fe/fereal", func_001A2128);

INCLUDE_ASM("fe/fereal", func_001A2190);

INCLUDE_ASM("fe/fereal", func_001A2208);

INCLUDE_ASM("fe/fereal", func_001A27A0);

INCLUDE_ASM("fe/fereal", cRealFE_loadCharAnimations);

INCLUDE_ASM("fe/fereal", func_001A2BC0);

INCLUDE_ASM("fe/fereal", cRealFE_loadStartState);

INCLUDE_ASM("fe/fereal", func_001A2E20);

INCLUDE_ASM("fe/fereal", func_001A2E58);

INCLUDE_ASM("fe/fereal", func_001A2F38);

INCLUDE_ASM("fe/fereal", func_001A2F70);

