#include "common.h"

INCLUDE_ASM("world/wscriptcache", cWScriptCache_init);

INCLUDE_ASM("world/wscriptcache", func_003AC8F0);

INCLUDE_ASM("world/wscriptcache", func_003ACA10);

// 0xc-byte elements reached through a pointer at self+0x4
struct sWScriptCacheEntry {
    char pad_0x00[0x8];
    int field_0x8;
};

//100%
INCLUDE_ASM("world/wscriptcache", func_003ACA38);
#ifdef SKIP_ASM
extern "C" int func_003ACA38(void* self, int a1)
{
    sWScriptCacheEntry* p = *(sWScriptCacheEntry**)((char*)self + 0x4);
    return p[a1].field_0x8;
}
#endif

//100%
INCLUDE_ASM("world/wscriptcache", func_003ACA50__FPv);
#ifdef SKIP_ASM
void* func_003ACA50(void* self)
{
    int t0 = 0;
    *(short*)self = (short)t0;
    *(int*)((char*)self + 0x4) = -1;
    *(int*)((char*)self + 0x8) = t0;
    *(short*)((char*)self + 0x2) = (short)t0;
    return self;
}
#endif

INCLUDE_ASM("world/wscriptcache", func_003ACA70);

INCLUDE_ASM("world/wscriptcache", func_003ACC50);

INCLUDE_ASM("world/wscriptcache", func_003ACC90);

INCLUDE_ASM("world/wscriptcache", func_003ACCD8);

INCLUDE_ASM("world/wscriptcache", func_003AD120);

INCLUDE_ASM("world/wscriptcache", func_003AD188);

INCLUDE_ASM("world/wscriptcache", func_003AD198);

INCLUDE_ASM("world/wscriptcache", func_003AD1A8);

extern "C" void* func_002E27E8(void* self);

//100%
INCLUDE_ASM("world/wscriptcache", func_003AD230__FPv);
#ifdef SKIP_ASM
void* func_003AD230(void* self)
{
    return func_002E27E8(self);
}
#endif

INCLUDE_ASM("world/wscriptcache", func_003AD290);

INCLUDE_ASM("world/wscriptcache", func_003ADC18);

//100%
INCLUDE_ASM("world/wscriptcache", func_003ADC48__FPv);
#ifdef SKIP_ASM
int func_003ADC48(void* self)
{
    return 0x1;
}
#endif

INCLUDE_ASM("world/wscriptcache", func_003ADC50);

INCLUDE_ASM("world/wscriptcache", func_003ADC80);

INCLUDE_ASM("world/wscriptcache", func_003ADCB0);

INCLUDE_ASM("world/wscriptcache", func_003ADCE0);

INCLUDE_ASM("world/wscriptcache", func_003ADD10);

INCLUDE_ASM("world/wscriptcache", func_003ADD40);

INCLUDE_ASM("world/wscriptcache", func_003ADD70);

extern "C" void* func_003AD290(int, int);

//99.38%
INCLUDE_ASM("world/wscriptcache", func_003ADDA0__FPv);
#ifdef SKIP_ASM
void* func_003ADDA0(void* self)
{
    return func_003AD290(1, 0xffff);
}
#endif

INCLUDE_ASM("world/wscriptcache", func_003ADDC0);

INCLUDE_ASM("world/wscriptcache", func_003ADE08);

INCLUDE_ASM("world/wscriptcache", func_003ADEC8);

INCLUDE_ASM("world/wscriptcache", func_003AE300);

INCLUDE_ASM("world/wscriptcache", func_003AE450);

INCLUDE_ASM("world/wscriptcache", func_003AE6C8);

INCLUDE_ASM("world/wscriptcache", func_003AE780);

INCLUDE_ASM("world/wscriptcache", func_003AE860);

INCLUDE_ASM("world/wscriptcache", func_003AE888);

extern "C" void* func_003AE888(void*, int);

//100%
INCLUDE_ASM("world/wscriptcache", func_003AE938__FPv);
#ifdef SKIP_ASM
void* func_003AE938(void* self)
{
    return func_003AE888(self, 0);
}
#endif

extern "C" void* func_003AE888(void*, int);

//100%
INCLUDE_ASM("world/wscriptcache", func_003AE958__FPv);
#ifdef SKIP_ASM
void* func_003AE958(void* self)
{
    return func_003AE888(self, 0x1000);
}
#endif

INCLUDE_ASM("world/wscriptcache", func_003AE9A0);

INCLUDE_ASM("world/wscriptcache", func_003AEAD0);

extern "C" void* func_003AEAD0(int, void*);

//99.44%
INCLUDE_ASM("world/wscriptcache", func_003AECB8__FPvT0);
#ifdef SKIP_ASM
void* func_003AECB8(void* self, void* a1)
{
    return func_003AEAD0(*(int*)a1, self);
}
#endif

INCLUDE_ASM("world/wscriptcache", func_003AECE0);

extern "C" void* func_003AECE0(int, int);

//99.38%
INCLUDE_ASM("world/wscriptcache", func_003AED20__FPvT0i);
#ifdef SKIP_ASM
void* func_003AED20(void* self, void* a1, int a2)
{
    return func_003AECE0(*(int*)a1, a2);
}
#endif

INCLUDE_ASM("world/wscriptcache", func_003AED40);

INCLUDE_ASM("world/wscriptcache", func_003AEE30);

INCLUDE_ASM("world/wscriptcache", func_003AEE98);

INCLUDE_ASM("world/wscriptcache", func_003AEEF8);

INCLUDE_ASM("world/wscriptcache", func_003AEFA8);

extern void* D_00456890[];

//100%
INCLUDE_ASM("world/wscriptcache", func_003B0410__FPv);
#ifdef SKIP_ASM
void* func_003B0410(void* self)
{
    int t0 = 0;
    *(int*)self = t0;
    *(int*)((char*)self + 0xc) = (int)(void*)D_00456890;
    *(int*)((char*)self + 0x4) = t0;
    return self;
}
#endif

INCLUDE_ASM("world/wscriptcache", func_003B0430);

INCLUDE_ASM("world/wscriptcache", func_003B04A0);

INCLUDE_ASM("world/wscriptcache", func_003B04F8);

INCLUDE_ASM("world/wscriptcache", func_003B0538);

INCLUDE_ASM("world/wscriptcache", func_003B0580);

INCLUDE_ASM("world/wscriptcache", func_003B05C0);

INCLUDE_ASM("world/wscriptcache", func_003B0600);

INCLUDE_ASM("world/wscriptcache", func_003B0680);

INCLUDE_ASM("world/wscriptcache", func_003B06B0);

INCLUDE_ASM("world/wscriptcache", func_003B06F8);

//100%
INCLUDE_ASM("world/wscriptcache", func_003B0720__FPv);
#ifdef SKIP_ASM
void* func_003B0720(void* self)
{
    int t0 = 0;
    *(int*)((char*)self + 0x4) = t0;
    *(int*)((char*)self + 0x8) = t0;
    *(int*)self = t0;
    return self;
}
#endif

//100%
INCLUDE_ASM("world/wscriptcache", func_003B0738__FPv);
#ifdef SKIP_ASM
void* func_003B0738(void* self)
{
    int t0 = 0;
    *(int*)self = t0;
    *(int*)((char*)self + 0xc) = 2;
    *(int*)((char*)self + 0x4) = t0;
    *(int*)((char*)self + 0x8) = t0;
    return self;
}
#endif

//100%
INCLUDE_ASM("world/wscriptcache", func_003B0758);
#ifdef SKIP_ASM
extern "C" void* func_003B0758(void* self, int a1, int a2, int a3, int a4)
{
    *(int*)((char*)self + 0xc) = a4;
    *(int*)self = a1;
    *(int*)((char*)self + 0x4) = a2;
    *(int*)((char*)self + 0x8) = a3;
    return self;
}
#endif

INCLUDE_ASM("world/wscriptcache", func_003B0770);

extern "C" void* func_003B0770(int, int);

//99.38%
INCLUDE_ASM("world/wscriptcache", func_003B07B8__FPv);
#ifdef SKIP_ASM
void* func_003B07B8(void* self)
{
    return func_003B0770(1, 0xffff);
}
#endif

extern "C" void* func_003B0770(int, int);

//99.38%
INCLUDE_ASM("world/wscriptcache", func_003B07D8__FPv);
#ifdef SKIP_ASM
void* func_003B07D8(void* self)
{
    return func_003B0770(0, 0xffff);
}
#endif

INCLUDE_ASM("world/wscriptcache", func_003B07F8);

INCLUDE_ASM("world/wscriptcache", func_003B08E0);

INCLUDE_ASM("world/wscriptcache", func_003B0948);

INCLUDE_ASM("world/wscriptcache", func_003B09A0);

INCLUDE_ASM("world/wscriptcache", func_003B0B10);

INCLUDE_ASM("world/wscriptcache", func_003B0B40);

INCLUDE_ASM("world/wscriptcache", func_003B0C58);

//100%
INCLUDE_ASM("world/wscriptcache", func_003B0FA0__FPv);
#ifdef SKIP_ASM
int func_003B0FA0(void* self)
{
    return *(int*)((char*)self + 0x10);
}
#endif

// padded past the 8-byte gp-relative threshold so the compiler emits
// absolute lui/lo addressing like the target, instead of assuming small data
struct sD_00509508 { float value; int pad[2]; };
extern sD_00509508 D_00509508;

//100%
INCLUDE_ASM("world/wscriptcache", func_003B0FA8);
#ifdef SKIP_ASM
extern "C" float func_003B0FA8()
{
    return D_00509508.value;
}
#endif

INCLUDE_ASM("world/wscriptcache", func_003B0FB8);

INCLUDE_ASM("world/wscriptcache", func_003B1050);

INCLUDE_ASM("world/wscriptcache", func_003B10D0);

INCLUDE_ASM("world/wscriptcache", func_003B1140);

INCLUDE_ASM("world/wscriptcache", func_003B11A0);

//100%
INCLUDE_ASM("world/wscriptcache", func_003B11E8__FPv);
#ifdef SKIP_ASM
void func_003B11E8(void* self)
{
}
#endif

INCLUDE_ASM("world/wscriptcache", func_003B11F0);

INCLUDE_ASM("world/wscriptcache", func_003B1228);

// padded past the 8-byte gp-relative threshold so the compiler emits
// absolute lui/lo addressing like the target
struct sD_0050A088 { void* ptr; int pad[2]; };
extern sD_0050A088 D_0050A088;

//100%
INCLUDE_ASM("world/wscriptcache", func_003B1258);
#ifdef SKIP_ASM
extern "C" unsigned int func_003B1258(int a0)
{
    return *(unsigned int*)((char*)D_0050A088.ptr + 0x4) >> (unsigned int)(-a0);
}
#endif

extern "C" void* func_003B1300(int);

//100%
INCLUDE_ASM("world/wscriptcache", func_003B1270__FPv);
#ifdef SKIP_ASM
void* func_003B1270(void* self)
{
    return func_003B1300(1);
}
#endif

INCLUDE_ASM("world/wscriptcache", func_003B1290);

INCLUDE_ASM("world/wscriptcache", func_003B1300);

INCLUDE_ASM("world/wscriptcache", func_003B1340);

INCLUDE_ASM("world/wscriptcache", func_003B13A8);

INCLUDE_ASM("world/wscriptcache", func_003B13D8);

INCLUDE_ASM("world/wscriptcache", func_003B1498);

INCLUDE_ASM("world/wscriptcache", func_003B14F0);

INCLUDE_ASM("world/wscriptcache", func_003B16E0);

INCLUDE_ASM("world/wscriptcache", func_003B17A8);

INCLUDE_ASM("world/wscriptcache", func_003B1988);

INCLUDE_ASM("world/wscriptcache", func_003B1AB0);

INCLUDE_ASM("world/wscriptcache", func_003B1CC0);

INCLUDE_ASM("world/wscriptcache", func_003B1D58);

INCLUDE_ASM("world/wscriptcache", func_003B1EE0);

INCLUDE_ASM("world/wscriptcache", func_003B1FC8);

INCLUDE_ASM("world/wscriptcache", func_003B20B8);

INCLUDE_ASM("world/wscriptcache", func_003B2230);

INCLUDE_ASM("world/wscriptcache", func_003B22F8);

INCLUDE_ASM("world/wscriptcache", func_003B2318);

//100%
INCLUDE_ASM("world/wscriptcache", func_003B2360__FPv);
#ifdef SKIP_ASM
void* func_003B2360(void* self)
{
    return func_003B1300(1);
}
#endif

extern "C" void* func_003B1498(void* self);

//100%
INCLUDE_ASM("world/wscriptcache", func_003B2380__FPv);
#ifdef SKIP_ASM
void* func_003B2380(void* self)
{
    return func_003B1498(self);
}
#endif

INCLUDE_ASM("world/wscriptcache", func_003B23A0);

INCLUDE_ASM("world/wscriptcache", func_003B2440);

INCLUDE_ASM("world/wscriptcache", func_003B2528);

INCLUDE_ASM("world/wscriptcache", func_003B2558);

INCLUDE_ASM("world/wscriptcache", func_003B2688);

INCLUDE_ASM("world/wscriptcache", func_003B26B8);

INCLUDE_ASM("world/wscriptcache", func_003B27C8);

INCLUDE_ASM("world/wscriptcache", func_003B2A68);

INCLUDE_ASM("world/wscriptcache", func_003B2B68);

INCLUDE_ASM("world/wscriptcache", func_003B2B90);

INCLUDE_ASM("world/wscriptcache", func_003B2E78);

INCLUDE_ASM("world/wscriptcache", func_003B3308);

INCLUDE_ASM("world/wscriptcache", func_003B33B0);

