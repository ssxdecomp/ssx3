#include "common.h"

INCLUDE_ASM("fe/festateruleselect", cFEStateRuleSelect_setupMenu);

INCLUDE_ASM("fe/festateruleselect", cFEStateRuleSelect_onCreateScreen);

extern "C" void* func_0039E4C0(void* self);

//100%
INCLUDE_ASM("fe/festateruleselect", func_00191C48__FPv);
#ifdef SKIP_ASM
void* func_00191C48(void* self)
{
    return func_0039E4C0(self);
}
#endif

INCLUDE_ASM("fe/festateruleselect", func_00191C68);

INCLUDE_ASM("fe/festateruleselect", func_00191E08);

INCLUDE_ASM("fe/festateruleselect", func_00191E48);

INCLUDE_ASM("fe/festateruleselect", func_00192088);

INCLUDE_ASM("fe/festateruleselect", func_00192240);

INCLUDE_ASM("fe/festateruleselect", func_00192380);

INCLUDE_ASM("fe/festateruleselect", cFEStateRuleSelect_updateMenuColor);

INCLUDE_ASM("fe/festateruleselect", func_001926F0);

INCLUDE_ASM("fe/festateruleselect", func_00192740);

INCLUDE_ASM("fe/festateruleselect", func_001927B0);

INCLUDE_ASM("fe/festateruleselect", func_00192918);

//100%
INCLUDE_ASM("fe/festateruleselect", func_00192948);
#ifdef SKIP_ASM
extern "C" int func_00192948(void* self, int a1)
{
    int mask = (int)(0x1000000 << a1) >> 24;
    return (*(int*)((char*)self + 0x2c) & mask) != 0;
}
#endif

//100%
INCLUDE_ASM("fe/festateruleselect", func_00192968__FPvi);
#ifdef SKIP_ASM
void func_00192968(void* self, int val)
{
    *(int*)((char*)self + 0x2C) = val;
}
#endif

INCLUDE_ASM("fe/festateruleselect", func_00192970);

INCLUDE_ASM("fe/festateruleselect", func_00192D00);

