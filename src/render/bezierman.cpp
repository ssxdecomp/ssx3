#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
void* cPSPBezierMan_cPSPBezierMan(void* self);
extern const char D_00492EA0[];

//99.23%
INCLUDE_ASM("render/bezierman", cBezierMan_construct__Fv);
#ifdef SKIP_ASM
void* cBezierMan_construct()
{
    void* mem = cMemMan_alloc(0x9C90, D_00492EA0, 0, 0);
    return cPSPBezierMan_cPSPBezierMan(mem);
}
#endif

INCLUDE_ASM("render/bezierman", func_0038AF30);

INCLUDE_ASM("render/bezierman", func_0038B0F8);

extern "C" void* func_003739D0(void*);

//100%
INCLUDE_ASM("render/bezierman", func_0038B158__FPv);
#ifdef SKIP_ASM
void* func_0038B158(void* self)
{
    return func_003739D0((char*)self + 0x10);
}
#endif

//99.2%
INCLUDE_ASM("render/bezierman", func_0038B178__FPv);
#ifdef SKIP_ASM
void func_0038B178(void* self)
{
    int t0 = 0;
    *(int*)((char*)self + 0x4d84) = t0;
    *(int*)((char*)self + 0x458) = t0;
    *(int*)((char*)self + 0x3c9c) = t0;
    *(int*)((char*)self + 0x4a60) = t0;
}
#endif

INCLUDE_ASM("render/bezierman", func_0038B190);

INCLUDE_ASM("render/bezierman", func_0038B338);

INCLUDE_ASM("render/bezierman", func_0038B370);

INCLUDE_ASM("render/bezierman", func_0038C788);

INCLUDE_ASM("render/bezierman", func_0038CA08);

INCLUDE_ASM("render/bezierman", func_0038CA70);

INCLUDE_ASM("render/bezierman", func_0038CE20);

INCLUDE_ASM("render/bezierman", func_0038D168);

INCLUDE_ASM("render/bezierman", func_0038D448);

INCLUDE_ASM("render/bezierman", func_0038D638);

//100%
INCLUDE_ASM("render/bezierman", func_0038D660__FPv);
#ifdef SKIP_ASM
void func_0038D660(void* self)
{
}
#endif

INCLUDE_ASM("render/bezierman", func_0038D690);

INCLUDE_ASM("render/bezierman", func_0038D968);

