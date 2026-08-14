#include "common.h"

INCLUDE_ASM("fe/festateload", cFEStateEventSelect_onCreateScreen);

extern "C" void* func_002009D0(void*);

//100%
INCLUDE_ASM("fe/festateload", func_00186708__FPv);
#ifdef SKIP_ASM
void* func_00186708(void* self)
{
    return func_002009D0((char*)self + 0x48);
}
#endif

extern "C" void* func_00200A70(void*);

//100%
INCLUDE_ASM("fe/festateload", func_00186728__FPv);
#ifdef SKIP_ASM
void* func_00186728(void* self)
{
    return func_00200A70((char*)self + 0x48);
}
#endif

INCLUDE_ASM("fe/festateload", func_00186748);

INCLUDE_ASM("fe/festateload", func_00186778);

INCLUDE_ASM("fe/festateload", func_001867A8);

INCLUDE_ASM("fe/festateload", func_00186950);

void func_00202768(void*);

//100%
INCLUDE_ASM("fe/festateload", func_00186978);
#ifdef SKIP_ASM
extern "C" void func_00186978(void* self)
{
    func_00202768((char*)self + 0x48);
}
#endif

INCLUDE_ASM("fe/festateload", func_00186998);

INCLUDE_ASM("fe/festateload", func_001869D8);

INCLUDE_ASM("fe/festateload", func_00186A08);

INCLUDE_ASM("fe/festateload", func_00186B18);

//100%
INCLUDE_ASM("fe/festateload", func_00186B48__FPv);
#ifdef SKIP_ASM
int func_00186B48(void* self)
{
    return 0x100;
}
#endif

