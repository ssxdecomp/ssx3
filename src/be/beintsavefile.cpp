#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern const char D_0045A7E0[];
extern void* D_0045AD08[16];
extern void* D_004A121C;
extern int D_004A1228;

struct cBESaveInterface {
    char pad_0x00[8];
    int field_0x8;
    void* vtable;
};

//99.8%
INCLUDE_ASM("be/beintsavefile", cBESaveInterface_getThis__Fv);
#ifdef SKIP_ASM
void* cBESaveInterface_getThis()
{
    if (D_004A121C == 0) {
        cBESaveInterface* mem = (cBESaveInterface*)cMemMan_alloc(0x10, D_0045A7E0, 0, 0);
        mem->field_0x8 = 0;
        mem->vtable = D_0045AD08;
        D_004A121C = mem;
        D_004A1228 = 0;
    }
    return D_004A121C;
}
#endif

INCLUDE_ASM("be/beintsavefile", func_00152688);

INCLUDE_ASM("be/beintsavefile", func_001526D0);

INCLUDE_ASM("be/beintsavefile", func_00152700);

INCLUDE_ASM("be/beintsavefile", func_00152728);

INCLUDE_ASM("be/beintsavefile", func_00152758);

INCLUDE_ASM("be/beintsavefile", func_00152948);

INCLUDE_ASM("be/beintsavefile", func_00152950);

INCLUDE_ASM("be/beintsavefile", func_00152BA8);

INCLUDE_ASM("be/beintsavefile", func_00152BB0);

INCLUDE_ASM("be/beintsavefile", func_00152DE0);

INCLUDE_ASM("be/beintsavefile", func_00153050);

