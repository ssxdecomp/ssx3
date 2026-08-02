#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern const char D_0045A718[];
extern void* D_0045AC78[16];
extern void* D_004A1214;

struct cBEEconInterface {
    char pad_0x00[8];
    int field_0x8;
    void* vtable;
};

//99.58%
INCLUDE_ASM("be/beintecon", cBEEconInterface_getThis__Fv);
#ifdef SKIP_ASM
void* cBEEconInterface_getThis()
{
    if (D_004A1214 == 0) {
        cBEEconInterface* mem = (cBEEconInterface*)cMemMan_alloc(0x10, D_0045A718, 0, 0);
        mem->field_0x8 = 0;
        mem->vtable = D_0045AC78;
        D_004A1214 = mem;
    }
    return D_004A1214;
}
#endif

INCLUDE_ASM("be/beintecon", func_00150928);

INCLUDE_ASM("be/beintecon", func_00150960);

extern int D_004A6CA8[];

//100%
INCLUDE_ASM("be/beintecon", cBEEconInterface_getTotalMoneyEarned__FPvii);
#ifdef SKIP_ASM
int cBEEconInterface_getTotalMoneyEarned(void* self, int a, int b)
{
    if (a >= 2) {
        return 0;
    }
    int bOff = b * 0xF88;
    int aOff = a * 0x9B50;
    int off = bOff + aOff;
    char* p = (char*)D_004A6CA8 + off;
    return *(int*)(p + 0xAC8);
}
#endif

INCLUDE_ASM("be/beintecon", func_001509F8);

INCLUDE_ASM("be/beintecon", func_00150A90);

INCLUDE_ASM("be/beintecon", func_00150B48);

INCLUDE_ASM("be/beintecon", func_00150B88);

INCLUDE_ASM("be/beintecon", func_00150C20);

extern void* D_00440550[];

//92.33%
INCLUDE_ASM("be/beintecon", func_00150E50__FPvi);
#ifdef SKIP_ASM
int func_00150E50(void* self, int a1)
{
    return *(int*)((char*)((char*)(void*)D_00440550 + a1 * 8) + 0x4);
}
#endif

INCLUDE_ASM("be/beintecon", func_00151040);

INCLUDE_ASM("be/beintecon", func_00151178);

INCLUDE_ASM("be/beintecon", func_001511B0);

INCLUDE_ASM("be/beintecon", func_00151368);

INCLUDE_ASM("be/beintecon", func_001513B8);

INCLUDE_ASM("be/beintecon", func_001515B8);

INCLUDE_ASM("be/beintecon", func_00151600);

INCLUDE_ASM("be/beintecon", func_001519E0);

INCLUDE_ASM("be/beintecon", func_00151A88);

INCLUDE_ASM("be/beintecon", func_00151C48);

INCLUDE_ASM("be/beintecon", func_00151C90);

INCLUDE_ASM("be/beintecon", func_00151EF0);

INCLUDE_ASM("be/beintecon", func_001520E8);

INCLUDE_ASM("be/beintecon", func_001521F0);

