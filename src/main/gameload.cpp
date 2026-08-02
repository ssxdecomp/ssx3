#include "common.h"

INCLUDE_ASM("main/gameload", cGame_load);

INCLUDE_ASM("main/gameload", cGame_loadTrack);

INCLUDE_ASM("main/gameload", func_0022FA98);

INCLUDE_ASM("main/gameload", func_00230050);

INCLUDE_ASM("main/gameload", func_002300F0);

INCLUDE_ASM("main/gameload", func_00230180);

INCLUDE_ASM("main/gameload", cGame_restart);

INCLUDE_ASM("main/gameload", func_00230338);

INCLUDE_ASM("main/gameload", func_00230360);

INCLUDE_ASM("main/gameload", func_00230430);

INCLUDE_ASM("main/gameload", cGame_exit);

INCLUDE_ASM("main/gameload", func_002305C8);

INCLUDE_ASM("main/gameload", func_00230640);

//95.0%
INCLUDE_ASM("main/gameload", func_00230698__FPvi);
#ifdef SKIP_ASM
int func_00230698(void* self, int a1)
{
    return *(int*)((char*)((char*)self + a1 * 4) + 0x5c);
}
#endif

//95.0%
INCLUDE_ASM("main/gameload", func_002306A8__FPvi);
#ifdef SKIP_ASM
int func_002306A8(void* self, int a1)
{
    return *(int*)((char*)((char*)self + a1 * 4) + 0x68);
}
#endif

INCLUDE_ASM("main/gameload", func_002306B8);

INCLUDE_ASM("main/gameload", func_00230E98);

INCLUDE_ASM("main/gameload", func_00230F40);

INCLUDE_ASM("main/gameload", func_00231250);

//100%
INCLUDE_ASM("main/gameload", func_00231278__FPvi);
#ifdef SKIP_ASM
void func_00231278(void* self, int val)
{
    *(int*)((char*)self + 0x208) = val;
}
#endif

INCLUDE_ASM("main/gameload", func_002312D8);

INCLUDE_ASM("main/gameload", func_00231320);

INCLUDE_ASM("main/gameload", func_00231348);

INCLUDE_ASM("main/gameload", func_002314D0);

INCLUDE_ASM("main/gameload", func_00231840);

INCLUDE_ASM("main/gameload", func_00231AB8);

INCLUDE_ASM("main/gameload", func_00231C70);

extern "C" void* func_00231D18(void* self);

//100%
INCLUDE_ASM("main/gameload", func_00231CB0__FPv);
#ifdef SKIP_ASM
void* func_00231CB0(void* self)
{
    return func_00231D18(self);
}
#endif

INCLUDE_ASM("main/gameload", func_00231CD0);

INCLUDE_ASM("main/gameload", func_00231CF0);

INCLUDE_ASM("main/gameload", func_00231D18);

INCLUDE_ASM("main/gameload", func_00231D60);

INCLUDE_ASM("main/gameload", func_00231F80);

INCLUDE_ASM("main/gameload", func_00231FC0);

extern void* D_0047D938[];

//100%
INCLUDE_ASM("main/gameload", func_00232328__FPv);
#ifdef SKIP_ASM
void* func_00232328(void* self)
{
    int t0 = 0;
    *(int*)((char*)self + 0x4) = t0;
    *(int*)self = (int)(void*)D_0047D938;
    *(int*)((char*)self + 0x8) = t0;
    return self;
}
#endif

