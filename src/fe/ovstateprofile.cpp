#include "common.h"

INCLUDE_ASM("fe/ovstateprofile", cOVState_PROFILE_onCreateScreen);

INCLUDE_ASM("fe/ovstateprofile", func_00211220);

INCLUDE_ASM("fe/ovstateprofile", func_00211270);

INCLUDE_ASM("fe/ovstateprofile", func_00211380);

INCLUDE_ASM("fe/ovstateprofile", func_00211850);

INCLUDE_ASM("fe/ovstateprofile", func_00211970);

INCLUDE_ASM("fe/ovstateprofile", func_00211A08);

INCLUDE_ASM("fe/ovstateprofile", func_00211AA8);

extern "C" void* func_001D58B8(void*);

//73.3%
INCLUDE_ASM("fe/ovstateprofile", func_00211B10__FPv);
#ifdef SKIP_ASM
void* func_00211B10(void* self)
{
    *(int*)((char*)self + 0x1a4) = 0;
    return func_001D58B8(self);
}
#endif

INCLUDE_ASM("fe/ovstateprofile", func_00211B38);

INCLUDE_ASM("fe/ovstateprofile", func_00211BC8);

INCLUDE_ASM("fe/ovstateprofile", func_00212080);

INCLUDE_ASM("fe/ovstateprofile", func_00212138);

INCLUDE_ASM("fe/ovstateprofile", cOVState_AUTOSAVE_onCreateScreen);

INCLUDE_ASM("fe/ovstateprofile", func_00212208);

//100%
INCLUDE_ASM("fe/ovstateprofile", func_002122E0__FPv);
#ifdef SKIP_ASM
int func_002122E0(void* self)
{
    return 0;
}
#endif

INCLUDE_ASM("fe/ovstateprofile", func_002122E8);

INCLUDE_ASM("fe/ovstateprofile", cOVState_AUTOSAVE_displayOn);

INCLUDE_ASM("fe/ovstateprofile", func_002124C8);

INCLUDE_ASM("fe/ovstateprofile", func_00212508);

