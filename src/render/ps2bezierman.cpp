#include "common.h"

extern "C" void func_00374C90(void* self);
extern "C" void func_00372B30(void* self);
extern "C" void func_0038AF30(void* self);
extern void* D_00493760[16];

//88.42%
INCLUDE_ASM("render/ps2bezierman", cPSPBezierMan_cPSPBezierMan__FPv);
#ifdef SKIP_ASM
void* cPSPBezierMan_cPSPBezierMan(void* self)
{
    func_00374C90(self);
    *(void**)((char*)self + 0x4) = D_00493760;
    func_00372B30((char*)self + 0x10);
    func_0038AF30(self);
    return self;
}
#endif

INCLUDE_ASM("render/ps2bezierman", func_0038AEB0);

