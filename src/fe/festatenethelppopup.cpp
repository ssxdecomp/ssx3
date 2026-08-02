#include "common.h"

INCLUDE_ASM("fe/festatenethelppopup", cFEStateNetHelpPopup_onCreateScreen);

INCLUDE_ASM("fe/festatenethelppopup", func_001D9E20);

INCLUDE_ASM("fe/festatenethelppopup", func_001D9E68);

//100%
INCLUDE_ASM("fe/festatenethelppopup", func_001D9F30__FPv);
#ifdef SKIP_ASM
int func_001D9F30(void* self)
{
    return 0x1;
}
#endif

INCLUDE_ASM("fe/festatenethelppopup", cFEStateNetHelpPopup_onWidgetCreate);

INCLUDE_ASM("fe/festatenethelppopup", func_001DA110);

INCLUDE_ASM("fe/festatenethelppopup", func_001DA238);

INCLUDE_ASM("fe/festatenethelppopup", func_001DA478);

INCLUDE_ASM("fe/festatenethelppopup", func_001DA4A8);

//61.67%
INCLUDE_ASM("fe/festatenethelppopup", func_001DA510__FPviii);
#ifdef SKIP_ASM
void* func_001DA510(void* self, int a1, int a2, int a3)
{
    *(int*)((char*)((char*)self + a1 * 4) + 0x68) = a2;
    *(int*)((char*)((char*)self + a1 * 4) + 0x84) = a3;
    return ((char*)self + a1 * 4);
}
#endif

//100%
INCLUDE_ASM("fe/festatenethelppopup", func_001DA528__FPvi);
#ifdef SKIP_ASM
void func_001DA528(void* self, int val)
{
    *(int*)((char*)self + 0x48) = val;
}
#endif

//95.0%
INCLUDE_ASM("fe/festatenethelppopup", func_001DA530__FPvii);
#ifdef SKIP_ASM
void func_001DA530(void* self, int a1, int a2)
{
    *(int*)((char*)((char*)self + a1 * 4) + 0x58) = a2;
}
#endif

INCLUDE_ASM("fe/festatenethelppopup", func_001DA648);

INCLUDE_ASM("fe/festatenethelppopup", func_001DA7E8);

INCLUDE_ASM("fe/festatenethelppopup", func_001DA988);

INCLUDE_ASM("fe/festatenethelppopup", func_001DAAC8);

INCLUDE_ASM("fe/festatenethelppopup", func_001DABD0);

INCLUDE_ASM("fe/festatenethelppopup", func_001DACB8);

INCLUDE_ASM("fe/festatenethelppopup", func_001DAE20);

INCLUDE_ASM("fe/festatenethelppopup", func_001DAF08);

INCLUDE_ASM("fe/festatenethelppopup", func_001DB028);

