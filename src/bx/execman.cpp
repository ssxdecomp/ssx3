#include "common.h"

struct cExecutionMan {
    int field_0x0;
    int field_0x4;
    void* field_0x8;
};

extern void* D_0048DC30[16];
void operator_delete(int* ptr);

//100%
INCLUDE_ASM("bx/execman", cExecutionMan__cExecutionMan__FP13cExecutionMani);
#ifdef SKIP_ASM
void cExecutionMan__cExecutionMan(cExecutionMan* self, int flags)
{
    self->field_0x8 = D_0048DC30;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}
#endif

//100%
INCLUDE_ASM("bx/execman", cExecutionMan_prepause__Fv);
#ifdef SKIP_ASM
void cExecutionMan_prepause()
{
}
#endif

//100%
INCLUDE_ASM("bx/execman", cExecutionMan_postpause__Fv);
#ifdef SKIP_ASM
void cExecutionMan_postpause()
{
}
#endif

INCLUDE_ASM("bx/execman", func_00320AD8);

INCLUDE_ASM("bx/execman", func_00320B08);

INCLUDE_ASM("bx/execman", func_00320B28);

INCLUDE_ASM("bx/execman", func_00320B48);

INCLUDE_ASM("bx/execman", func_00320B68);

INCLUDE_ASM("bx/execman", func_00320BF0);

INCLUDE_ASM("bx/execman", func_00320C48);

