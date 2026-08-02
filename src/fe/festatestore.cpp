#include "common.h"

INCLUDE_ASM("fe/festatestore", cFEStateUberTrick_costVisible);

INCLUDE_ASM("fe/festatestore", func_00184780);

INCLUDE_ASM("fe/festatestore", cFEStateUberTrick_trickVisible);

INCLUDE_ASM("fe/festatestore", func_001849B0);

INCLUDE_ASM("fe/festatestore", func_00184B70);

INCLUDE_ASM("fe/festatestore", func_00184BB8);

INCLUDE_ASM("fe/festatestore", func_00184BE0);

INCLUDE_ASM("fe/festatestore", func_00184C60);

INCLUDE_ASM("fe/festatestore", func_00184F40);

INCLUDE_ASM("fe/festatestore", cFEStateUberTrick_onWidgetCreate);

INCLUDE_ASM("fe/festatestore", func_00185268);

INCLUDE_ASM("fe/festatestore", func_001859D8);

INCLUDE_ASM("fe/festatestore", func_00185A18);

extern void* D_0046D0D0[];
extern "C" void* func_0039E390(void*);

//100%
INCLUDE_ASM("fe/festatestore", func_00185A70__FPv);
#ifdef SKIP_ASM
void* func_00185A70(void* self)
{
    *(int*)((char*)self + 0x8) = (int)(void*)D_0046D0D0;
    return func_0039E390(self);
}
#endif

