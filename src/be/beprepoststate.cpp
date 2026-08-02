#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);

struct sStateSingleton {
    void* field_0x0;
    void* vtable;
};

extern const char D_0045A8A8[];
extern void* D_0045ABB8[16];
extern void* D_004A1254;

//99.86%
INCLUDE_ASM("be/beprepoststate", cBEPostRaceState_getState__FPv);
#ifdef SKIP_ASM
void* cBEPostRaceState_getState(void* self)
{
    if (D_004A1254 == 0) {
        sStateSingleton* mem = (sStateSingleton*)cMemMan_alloc(8, D_0045A8A8, 0, 0);
        mem->field_0x0 = self;
        mem->vtable = D_0045ABB8;
        D_004A1254 = mem;
    }
    return D_004A1254;
}
#endif

INCLUDE_ASM("be/beprepoststate", func_00156390);

INCLUDE_ASM("be/beprepoststate", func_001564B0);

INCLUDE_ASM("be/beprepoststate", func_00156510);

extern void* D_0045AC18[16];
extern void* D_004A1258;

//99.86%
INCLUDE_ASM("be/beprepoststate", cBEPreRaceState_getState__FPv);
#ifdef SKIP_ASM
void* cBEPreRaceState_getState(void* self)
{
    if (D_004A1258 == 0) {
        sStateSingleton* mem = (sStateSingleton*)cMemMan_alloc(8, D_0045A8A8, 0, 0);
        mem->field_0x0 = self;
        mem->vtable = D_0045AC18;
        D_004A1258 = mem;
    }
    return D_004A1258;
}
#endif

INCLUDE_ASM("be/beprepoststate", func_001565C8);

INCLUDE_ASM("be/beprepoststate", func_001566E8);

INCLUDE_ASM("be/beprepoststate", func_00156750);

INCLUDE_ASM("be/beprepoststate", func_001567B8);

INCLUDE_ASM("be/beprepoststate", func_00156810);

INCLUDE_ASM("be/beprepoststate", func_00156858);

INCLUDE_ASM("be/beprepoststate", func_00156950);

INCLUDE_ASM("be/beprepoststate", func_00156988);

