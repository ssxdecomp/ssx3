#include "common.h"

INCLUDE_ASM("luno/lunovm", luno_cLunoVM_execute);

INCLUDE_ASM("luno/lunovm", func_00224C00);

INCLUDE_ASM("luno/lunovm", func_00224C78);

INCLUDE_ASM("luno/lunovm", func_00224D00);

INCLUDE_ASM("luno/lunovm", func_00224DA0);

INCLUDE_ASM("luno/lunovm", func_00224DF0);

INCLUDE_ASM("luno/lunovm", luno_cLunoTable_constructTable);

INCLUDE_ASM("luno/lunovm", func_00224F30);

INCLUDE_ASM("luno/lunovm", func_00224F68);

INCLUDE_ASM("luno/lunovm", func_00225068);

INCLUDE_ASM("luno/lunovm", func_00225248);

INCLUDE_ASM("luno/lunovm", luno_cLunoTable_set);

INCLUDE_ASM("luno/lunovm", func_002257E0);

INCLUDE_ASM("luno/lunovm", func_002259A8);

INCLUDE_ASM("luno/lunovm", func_00225B90);

INCLUDE_ASM("luno/lunovm", func_00225BE8);

INCLUDE_ASM("luno/lunovm", func_00225CA0);

INCLUDE_ASM("luno/lunovm", func_00225DE8);

//96.0%
INCLUDE_ASM("luno/lunovm", func_00226600__FPvii);
#ifdef SKIP_ASM
void func_00226600(void* self, int a1, int a2)
{
    *(int*)((char*)self + 0x4) = a2;
    *(int*)self = a1;
}
#endif

//100%
INCLUDE_ASM("luno/lunovm", func_00226610__FPv);
#ifdef SKIP_ASM
void* func_00226610(void* self)
{
    return self;
}
#endif

//100%
INCLUDE_ASM("luno/lunovm", func_00226618__FPv);
#ifdef SKIP_ASM
void* func_00226618(void* self)
{
    return self;
}
#endif

//100%
INCLUDE_ASM("luno/lunovm", func_00226620__FPv);
#ifdef SKIP_ASM
void* func_00226620(void* self)
{
    return self;
}
#endif

INCLUDE_ASM("luno/lunovm", func_00226628);

INCLUDE_ASM("luno/lunovm", func_00226768);

INCLUDE_ASM("luno/lunovm", func_002267F0);

INCLUDE_ASM("luno/lunovm", func_00226810);

