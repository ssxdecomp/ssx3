#include "common.h"

INCLUDE_ASM("main/sectionman", cSectionMan_setSky);

INCLUDE_ASM("main/sectionman", func_0022E228);

//95.0%
INCLUDE_ASM("main/sectionman", func_0022E278__FPv);
#ifdef SKIP_ASM
int func_0022E278(void* self)
{
    *(int*)((char*)self + 0x198) = *(int*)((char*)*(void**)((char*)self + 0x198) + 0x4);
    return *(int*)((char*)self + 0x198);
}
#endif

//100%
INCLUDE_ASM("main/sectionman", func_0022E288__FPvT0);
#ifdef SKIP_ASM
int func_0022E288(void* self, void* a1)
{
    int t0 = *(int*)((char*)self + 0x198);
    *(int*)((char*)a1 + 0x4) = t0;
    *(int*)((char*)self + 0x198) = (int)a1;
    return t0;
}
#endif

INCLUDE_ASM("main/sectionman", func_0022E298);

//100%
INCLUDE_ASM("main/sectionman", func_0022E348);
#ifdef SKIP_ASM
extern "C" int func_0022E348(void* self, void* a1)
{
    if (a1 != 0) {
        return *(int*)((char*)a1 + 0x4);
    }
    return *(int*)((char*)self + 0x19c);
}
#endif

INCLUDE_ASM("main/sectionman", func_0022E360);

