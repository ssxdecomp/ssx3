#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);

struct sStateSingleton {
    void* field_0x0;
    void* vtable;
};

extern const char D_004A1230[];
extern void* D_0045ABE8[16];
extern void* D_004A122C;

//99.86%
INCLUDE_ASM("be/bestate", cBERaceState_getState__FPv);
#ifdef SKIP_ASM
void* cBERaceState_getState(void* self)
{
    if (D_004A122C == 0) {
        sStateSingleton* mem = (sStateSingleton*)cMemMan_alloc(8, D_004A1230, 0, 0);
        mem->field_0x0 = self;
        mem->vtable = D_0045ABE8;
        D_004A122C = mem;
    }
    return D_004A122C;
}
#endif

INCLUDE_ASM("be/bestate", func_001530E0);

INCLUDE_ASM("be/bestate", func_00153200);

INCLUDE_ASM("be/bestate", func_00153258);

