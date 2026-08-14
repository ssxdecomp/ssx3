#include "common.h"

INCLUDE_ASM("object/instancenode", cInstanceNode_cInstanceNode);

INCLUDE_ASM("object/instancenode", func_0034FBF0);

//100%
INCLUDE_ASM("object/instancenode", func_0034FC78);
#ifdef SKIP_ASM
extern "C" void func_0034FC78(int a0, void* a1)
{
    *(int*)((char*)a1 + 0xc) = a0;
}
#endif

//100%
INCLUDE_ASM("object/instancenode", func_0034FC80);
#ifdef SKIP_ASM
extern "C" void func_0034FC80(void* self, void* a1)
{
    if (a1 != 0) {
        if (*(int*)((char*)a1 + 0xc) == (int)self) {
            *(int*)((char*)a1 + 0xc) = 0;
        }
    }
}
#endif

extern "C" void* func_002D19E8(int);

//100%
INCLUDE_ASM("object/instancenode", func_0034FCC0__FPv);
#ifdef SKIP_ASM
void* func_0034FCC0(void* self)
{
    return func_002D19E8(*(int*)((char*)self + 0x18));
}
#endif

extern "C" void* func_002D1A30(int);

//100%
INCLUDE_ASM("object/instancenode", func_0034FCE0__FPv);
#ifdef SKIP_ASM
void* func_0034FCE0(void* self)
{
    return func_002D1A30(*(int*)((char*)self + 0x18));
}
#endif

INCLUDE_ASM("object/instancenode", func_0034FD00);

INCLUDE_ASM("object/instancenode", func_0034FD90);

extern "C" void* func_002D19B8(int, int, int);

//100%
INCLUDE_ASM("object/instancenode", func_0034FE00__FPviii);
#ifdef SKIP_ASM
void* func_0034FE00(void* self, int a1, int a2, int a3)
{
    return func_002D19B8(a1, a2, a3);
}
#endif

INCLUDE_ASM("object/instancenode", func_0034FE28);

INCLUDE_ASM("object/instancenode", func_0034FE90);

INCLUDE_ASM("object/instancenode", func_0034FED8);

INCLUDE_ASM("object/instancenode", func_00350288);

INCLUDE_ASM("object/instancenode", cInstanceNode_getBoundBoxInfo);

INCLUDE_ASM("object/instancenode", func_00350698);

INCLUDE_ASM("object/instancenode", func_003506D8);

