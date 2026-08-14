#include "common.h"

INCLUDE_ASM("fe/ovstatepause", cOVState_PAUSE_OPTIONS_onCreateScreen);

INCLUDE_ASM("fe/ovstatepause", func_001FA100);

INCLUDE_ASM("fe/ovstatepause", func_001FA238);

INCLUDE_ASM("fe/ovstatepause", func_001FA9E0);

INCLUDE_ASM("fe/ovstatepause", func_001FAA78);

//100%
INCLUDE_ASM("fe/ovstatepause", func_001FAAF0);
#ifdef SKIP_ASM
extern "C" int func_001FAAF0(void* self, int a1, int a2)
{
    return a2 != 4 ? 0x101 : 0x100;
}
#endif

//100%
INCLUDE_ASM("fe/ovstatepause", func_001FAB08);
#ifdef SKIP_ASM
extern "C" int func_001FAB08(void* self, int a1, int a2)
{
    return a2 != 0 ? 0x101 : 0x100;
}
#endif

INCLUDE_ASM("fe/ovstatepause", cOVState_PAUSE_ONLINE_ERROR_onCreateScreen);

//100%
INCLUDE_ASM("fe/ovstatepause", func_001FAF08__FPv);
#ifdef SKIP_ASM
int func_001FAF08(void* self)
{
    return 0x1;
}
#endif

INCLUDE_ASM("fe/ovstatepause", func_001FAF10);

INCLUDE_ASM("fe/ovstatepause", func_001FAFF8);

INCLUDE_ASM("fe/ovstatepause", func_001FB0C0);

INCLUDE_ASM("fe/ovstatepause", cOVState_PAUSE_ONLINE_ERROR_displayPingTimedOut);

INCLUDE_ASM("fe/ovstatepause", cOVState_PAUSE_ONLINE_ERROR_displayPingReceived);

INCLUDE_ASM("fe/ovstatepause", func_001FB2B8);

INCLUDE_ASM("fe/ovstatepause", cOVState_PAUSE_ONLINE_ERROR_setContinueOptionVisible);

INCLUDE_ASM("fe/ovstatepause", func_001FB458);

INCLUDE_ASM("fe/ovstatepause", func_001FB588);

INCLUDE_ASM("fe/ovstatepause", func_001FB6B8);

INCLUDE_ASM("fe/ovstatepause", func_001FBBD8);

INCLUDE_ASM("fe/ovstatepause", func_001FBCC8);

INCLUDE_ASM("fe/ovstatepause", func_001FBCE0);

INCLUDE_ASM("fe/ovstatepause", func_001FBD20);

INCLUDE_ASM("fe/ovstatepause", func_001FC768);

INCLUDE_ASM("fe/ovstatepause", func_001FC878);

INCLUDE_ASM("fe/ovstatepause", func_001FCEC0);

INCLUDE_ASM("fe/ovstatepause", func_001FD0D8);

INCLUDE_ASM("fe/ovstatepause", func_001FD118);

INCLUDE_ASM("fe/ovstatepause", func_001FD150);

INCLUDE_ASM("fe/ovstatepause", func_001FD190);

INCLUDE_ASM("fe/ovstatepause", func_001FD268);

INCLUDE_ASM("fe/ovstatepause", func_001FD320);

//100%
INCLUDE_ASM("fe/ovstatepause", func_001FDB78);
#ifdef SKIP_ASM
extern "C" int func_001FDB78(void* self, int a1, int a2)
{
    return a2 == 6 ? 0x101 : 0;
}
#endif

INCLUDE_ASM("fe/ovstatepause", func_001FDB88);

INCLUDE_ASM("fe/ovstatepause", func_001FDBF0);

INCLUDE_ASM("fe/ovstatepause", func_001FDC30);

INCLUDE_ASM("fe/ovstatepause", func_001FDE60);

INCLUDE_ASM("fe/ovstatepause", func_001FDF00);

INCLUDE_ASM("fe/ovstatepause", func_001FDF40);

INCLUDE_ASM("fe/ovstatepause", func_001FE4A8);

INCLUDE_ASM("fe/ovstatepause", func_001FE5B0);

INCLUDE_ASM("fe/ovstatepause", func_001FE648);

INCLUDE_ASM("fe/ovstatepause", func_001FE6E8);

INCLUDE_ASM("fe/ovstatepause", func_001FE8F0);

INCLUDE_ASM("fe/ovstatepause", func_001FE968);

INCLUDE_ASM("fe/ovstatepause", func_001FE9A8);

extern "C" void* func_001D58B8(void* self);

//100%
INCLUDE_ASM("fe/ovstatepause", func_001FEC40__FPv);
#ifdef SKIP_ASM
void* func_001FEC40(void* self)
{
    return func_001D58B8(self);
}
#endif

INCLUDE_ASM("fe/ovstatepause", func_001FEC60);

INCLUDE_ASM("fe/ovstatepause", func_001FECA0);

INCLUDE_ASM("fe/ovstatepause", func_001FF170);

INCLUDE_ASM("fe/ovstatepause", func_001FF278);

INCLUDE_ASM("fe/ovstatepause", func_001FF310);

INCLUDE_ASM("fe/ovstatepause", func_001FF3B0);

INCLUDE_ASM("fe/ovstatepause", cOVState_REWARDS_onCreateScreen);

INCLUDE_ASM("fe/ovstatepause", func_001FF6D0);

INCLUDE_ASM("fe/ovstatepause", func_001FF700);

INCLUDE_ASM("fe/ovstatepause", func_001FF748);

INCLUDE_ASM("fe/ovstatepause", func_001FF7B8);

INCLUDE_ASM("fe/ovstatepause", func_001FFD08);

INCLUDE_ASM("fe/ovstatepause", cOVState_REWARDS_onGainTransition);

