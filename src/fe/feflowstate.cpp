#include "common.h"

INCLUDE_ASM("fe/feflowstate", cFEFlowState_setNumStates);

INCLUDE_ASM("fe/feflowstate", func_001A06B0);

//100%
INCLUDE_ASM("fe/feflowstate", func_001A06F0);
#ifdef SKIP_ASM
extern "C" signed char func_001A06F0(void* self, int a1)
{
    return *(signed char*)(*(int*)((char*)self + 0x4) + (signed char)a1);
}
#endif

//100%
INCLUDE_ASM("fe/feflowstate", func_001A0708);
#ifdef SKIP_ASM
extern "C" void func_001A0708(void* self, int a1, int a2)
{
    *(char*)(*(int*)((char*)self + 0x4) + (signed char)a1) = a2;
}
#endif

