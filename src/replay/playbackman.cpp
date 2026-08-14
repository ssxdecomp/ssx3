#include "common.h"

INCLUDE_ASM("replay/playbackman", cPlaybackMan_cPlaybackMan);

INCLUDE_ASM("replay/playbackman", func_0026C588);

INCLUDE_ASM("replay/playbackman", cPlaybackMan_update);

INCLUDE_ASM("replay/playbackman", cPlaybackMan_initLocation);

INCLUDE_ASM("replay/playbackman", func_0026C898);

INCLUDE_ASM("replay/playbackman", func_0026CA90);

//100%
INCLUDE_ASM("replay/playbackman", func_0026CBB0__FPv);
#ifdef SKIP_ASM
void func_0026CBB0(void* self)
{
    *(int*)((char*)self + 0x10) = 0;
}
#endif

INCLUDE_ASM("replay/playbackman", func_0026CBB8);

INCLUDE_ASM("replay/playbackman", func_0026CC18);

INCLUDE_ASM("replay/playbackman", func_0026CC48);

INCLUDE_ASM("replay/playbackman", func_0026CD20);

extern "C" void* func_0026CC18(void*);

//72.8%
INCLUDE_ASM("replay/playbackman", func_0026CDD0__FPv);
#ifdef SKIP_ASM
void* func_0026CDD0(void* self)
{
    *(int*)((char*)self + 0x70) = 0;
    return func_0026CC18(self);
}
#endif

INCLUDE_ASM("replay/playbackman", func_0026CDF8);

INCLUDE_ASM("replay/playbackman", func_0026CE50);

INCLUDE_ASM("replay/playbackman", func_0026D0A0);

INCLUDE_ASM("replay/playbackman", func_0026D0E8);

INCLUDE_ASM("replay/playbackman", func_0026D130);

//99.25%
INCLUDE_ASM("replay/playbackman", func_0026D168__FPv);
#ifdef SKIP_ASM
void func_0026D168(void* self)
{
    int t0 = 0;
    *(int*)((char*)self + 0x8) = t0;
    *(int*)self = t0;
    *(int*)((char*)self + 0x4) = t0;
}
#endif

INCLUDE_ASM("replay/playbackman", func_0026D178);

INCLUDE_ASM("replay/playbackman", func_0026D228);

INCLUDE_ASM("replay/playbackman", func_0026D2B0);

INCLUDE_ASM("replay/playbackman", func_0026D420);

INCLUDE_ASM("replay/playbackman", func_0026D4D8);

INCLUDE_ASM("replay/playbackman", func_0026D558);

INCLUDE_ASM("replay/playbackman", func_0026D5E8);

INCLUDE_ASM("replay/playbackman", func_0026D628);

INCLUDE_ASM("replay/playbackman", func_0026D678);

//95.0%
INCLUDE_ASM("replay/playbackman", func_0026D730__FPvii);
#ifdef SKIP_ASM
void func_0026D730(void* self, int a1, int a2)
{
    *(int*)((char*)((char*)self + a1 * 4) + 0x20) = a2;
}
#endif

extern "C" void* func_0026E5D0(void*);

//100%
INCLUDE_ASM("replay/playbackman", func_0026D740__FPv);
#ifdef SKIP_ASM
void* func_0026D740(void* self)
{
    return func_0026E5D0((char*)self + 0x3b0);
}
#endif

INCLUDE_ASM("replay/playbackman", func_0026D760);

INCLUDE_ASM("replay/playbackman", func_0026D7D0);

INCLUDE_ASM("replay/playbackman", func_0026D818);

INCLUDE_ASM("replay/playbackman", func_0026D988);

INCLUDE_ASM("replay/playbackman", func_0026DA88);

INCLUDE_ASM("replay/playbackman", func_0026DB88);

extern "C" void cReplay_restoreFrame(void*);

//100%
INCLUDE_ASM("replay/playbackman", func_0026DBD0);
#ifdef SKIP_ASM
extern "C" void func_0026DBD0(void* self)
{
    cReplay_restoreFrame(self);
}
#endif

