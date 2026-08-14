#include "common.h"

INCLUDE_ASM("fe/messagecenter", cFEStateRequestLine_onWidgetCreate);

INCLUDE_ASM("fe/messagecenter", func_00197500);

INCLUDE_ASM("fe/messagecenter", func_001977D0);

INCLUDE_ASM("fe/messagecenter", func_001979D8);

INCLUDE_ASM("fe/messagecenter", func_00197AD8);

INCLUDE_ASM("fe/messagecenter", func_00197B88);

INCLUDE_ASM("fe/messagecenter", func_00197BC8);

INCLUDE_ASM("fe/messagecenter", func_00197CA0);

INCLUDE_ASM("fe/messagecenter", func_00197DB8);

INCLUDE_ASM("fe/messagecenter", func_00197E70);

INCLUDE_ASM("fe/messagecenter", func_00198118);

INCLUDE_ASM("fe/messagecenter", cFEStateRequestLine_updateHelpText);

INCLUDE_ASM("fe/messagecenter", cFEStateRequestLine_updateButtonsText);

INCLUDE_ASM("fe/messagecenter", func_001985B0);

INCLUDE_ASM("fe/messagecenter", func_001985F0);

INCLUDE_ASM("fe/messagecenter", cFEStateRequestLine_updateHilightedSongInfo);

INCLUDE_ASM("fe/messagecenter", func_001988D8);

INCLUDE_ASM("fe/messagecenter", func_00198988);

INCLUDE_ASM("fe/messagecenter", func_00198A88);

INCLUDE_ASM("fe/messagecenter", func_00198AB8);

//100%
INCLUDE_ASM("fe/messagecenter", func_00198AE8__FPv);
#ifdef SKIP_ASM
int func_00198AE8(void* self)
{
    return 0x1388;
}
#endif

INCLUDE_ASM("fe/messagecenter", func_00198AF0);

//100%
INCLUDE_ASM("fe/messagecenter", func_00198DA0);
#ifdef SKIP_ASM
extern "C" int func_00198DA0(void* self, void* a1)
{
    void* p = *(void**)self;
    void* p2 = *(void**)a1;
    return *(short*)((char*)p + 0xa) - *(short*)((char*)p2 + 0xa);
}
#endif

