#include "common.h"

INCLUDE_ASM("scripter/videngine", cVidEngine_ReadyVideo);

INCLUDE_ASM("scripter/videngine", func_002839A8);

INCLUDE_ASM("scripter/videngine", func_00283AA0);

INCLUDE_ASM("scripter/videngine", func_00283AF8);

INCLUDE_ASM("scripter/videngine", func_00283B78);

INCLUDE_ASM("scripter/videngine", func_00283BB8);

//99.25%
INCLUDE_ASM("scripter/videngine", func_00283C20__FPv);
#ifdef SKIP_ASM
void func_00283C20(void* self)
{
    int t0 = 0;
    *(int*)((char*)self + 0x94) = t0;
    *(int*)((char*)self + 0x8c) = t0;
    *(int*)((char*)self + 0x90) = t0;
}
#endif

INCLUDE_ASM("scripter/videngine", func_00283C30);

//100%
INCLUDE_ASM("scripter/videngine", func_00283C58__FPv);
#ifdef SKIP_ASM
int func_00283C58(void* self)
{
    return *(int*)((char*)self + 0x94);
}
#endif

//100%
INCLUDE_ASM("scripter/videngine", func_00283C60);
#ifdef SKIP_ASM
extern "C" int func_00283C60(void* self, int a1)
{
    if (a1 == 4) {
        return 0;
    }
    return a1 + 1;
}
#endif

INCLUDE_ASM("scripter/videngine", func_00283C80);

INCLUDE_ASM("scripter/videngine", func_00283D28);

INCLUDE_ASM("scripter/videngine", func_00283D70);

//100%
INCLUDE_ASM("scripter/videngine", func_00283DA0);
#ifdef SKIP_ASM
extern "C" int func_00283DA0(void* self)
{
    int r = 0;
    if (*(int*)((char*)self + 0x90) == *(int*)((char*)self + 0x8c)) {
        r = *(int*)((char*)self + 0x94) == 0;
    }
    return r;
}
#endif

INCLUDE_ASM("scripter/videngine", func_00283DC0);

