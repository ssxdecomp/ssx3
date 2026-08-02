#include "common.h"

INCLUDE_ASM("fe/festatebonusmaterial", cFEStateBonusMaterial_onCreateScreen);

INCLUDE_ASM("fe/festatebonusmaterial", func_00195540);

INCLUDE_ASM("fe/festatebonusmaterial", func_001955B8);

extern "C" void* func_0039E4C0(void* self);

//100%
INCLUDE_ASM("fe/festatebonusmaterial", func_001955E0__FPv);
#ifdef SKIP_ASM
void* func_001955E0(void* self)
{
    return func_0039E4C0(self);
}
#endif

INCLUDE_ASM("fe/festatebonusmaterial", func_00195600);

