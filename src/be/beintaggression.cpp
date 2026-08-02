#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern const char D_0045A898[];
extern void* D_0045AC48[16];
extern void* D_004A124C;

struct cBEAggressionInterface {
    char pad_0x00[8];
    int field_0x8;
    void* vtable;
};

//99.58%
INCLUDE_ASM("be/beintaggression", cBEAggressionInterface_getThis__Fv);
#ifdef SKIP_ASM
void* cBEAggressionInterface_getThis()
{
    if (D_004A124C == 0) {
        cBEAggressionInterface* mem = (cBEAggressionInterface*)cMemMan_alloc(0x10, D_0045A898, 0, 0);
        mem->field_0x8 = 0;
        mem->vtable = D_0045AC48;
        D_004A124C = mem;
    }
    return D_004A124C;
}
#endif

INCLUDE_ASM("be/beintaggression", func_00155AA0);

INCLUDE_ASM("be/beintaggression", func_00155AA8);

INCLUDE_ASM("be/beintaggression", func_00155AB0);

INCLUDE_ASM("be/beintaggression", func_00155B50);

INCLUDE_ASM("be/beintaggression", func_00155BF0);

INCLUDE_ASM("be/beintaggression", func_00155E58);

INCLUDE_ASM("be/beintaggression", func_001560A0);

INCLUDE_ASM("be/beintaggression", func_001561B0);

