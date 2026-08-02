#include "common.h"

INCLUDE_ASM("replay/replay", cReplay_restoreFrame);

INCLUDE_ASM("replay/replay", cReplay_restoreBucket);

INCLUDE_ASM("replay/replay", func_0026DE58);

INCLUDE_ASM("replay/replay", cReplay_restoreObject);

INCLUDE_ASM("replay/replay", cReplay_restoreDeadBucket);

extern "C" void* func_0026E6A0(void*);

//100%
INCLUDE_ASM("replay/replay", func_0026E448__FPv);
#ifdef SKIP_ASM
void* func_0026E448(void* self)
{
    return func_0026E6A0((char*)self + 0x3b0);
}
#endif

INCLUDE_ASM("replay/replay", func_0026E468);

INCLUDE_ASM("replay/replay", func_0026E490);

INCLUDE_ASM("replay/replay", func_0026E4B8);

INCLUDE_ASM("replay/replay", func_0026E528);

INCLUDE_ASM("replay/replay", func_0026E568);

//100%
INCLUDE_ASM("replay/replay", func_0026E5A8__FPv);
#ifdef SKIP_ASM
void* func_0026E5A8(void* self)
{
    int t0 = 0;
    *(int*)((char*)self + 0x4) = t0;
    *(int*)self = t0;
    *(int*)((char*)self + 0x8) = t0;
    return self;
}
#endif

//99.25%
INCLUDE_ASM("replay/replay", func_0026E5C0__FPv);
#ifdef SKIP_ASM
void func_0026E5C0(void* self)
{
    int t0 = 0;
    *(int*)((char*)self + 0x8) = t0;
    *(int*)((char*)self + 0x4) = t0;
    *(int*)self = t0;
}
#endif

INCLUDE_ASM("replay/replay", func_0026E5D0);

INCLUDE_ASM("replay/replay", func_0026E608);

INCLUDE_ASM("replay/replay", func_0026E670);

INCLUDE_ASM("replay/replay", func_0026E6A0);

INCLUDE_ASM("replay/replay", func_0026E6E0);

//100%
INCLUDE_ASM("replay/replay", func_0026E7F8__FPv);
#ifdef SKIP_ASM
void func_0026E7F8(void* self)
{
    *(int*)((char*)self + 0xB0) = 0;
}
#endif

INCLUDE_ASM("replay/replay", func_0026E800);

INCLUDE_ASM("replay/replay", func_0026E838);

INCLUDE_ASM("replay/replay", func_0026E8E0);

