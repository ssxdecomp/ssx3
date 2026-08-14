#include "common.h"

INCLUDE_ASM("object/splinemodifier", cSplineModifier_cSplineModifier);

INCLUDE_ASM("object/splinemodifier", func_00359688);

INCLUDE_ASM("object/splinemodifier", func_00359698);

INCLUDE_ASM("object/splinemodifier", func_00359830);

INCLUDE_ASM("object/splinemodifier", func_00359CF8);

INCLUDE_ASM("object/splinemodifier", func_00359EB8);

INCLUDE_ASM("object/splinemodifier", func_00359F30);

INCLUDE_ASM("object/splinemodifier", func_00359F88);

INCLUDE_ASM("object/splinemodifier", func_0035A118);

INCLUDE_ASM("object/splinemodifier", func_0035A250);

INCLUDE_ASM("object/splinemodifier", cMultiSplineModifier_allocNodes);

INCLUDE_ASM("object/splinemodifier", func_0035A3F0);

INCLUDE_ASM("object/splinemodifier", cMultiSplineModifier_setupNodes);

INCLUDE_ASM("object/splinemodifier", func_0035A550);

INCLUDE_ASM("object/splinemodifier", func_0035A560);

extern "C" void* func_0035AC20(void* self);

//100%
INCLUDE_ASM("object/splinemodifier", func_0035A5D8__FPv);
#ifdef SKIP_ASM
void* func_0035A5D8(void* self)
{
    return func_0035AC20(self);
}
#endif

INCLUDE_ASM("object/splinemodifier", cMultiSplineModifier_setupOverlapSystem);

INCLUDE_ASM("object/splinemodifier", func_0035A780);

INCLUDE_ASM("object/splinemodifier", func_0035A918);

//100%
INCLUDE_ASM("object/splinemodifier", func_0035AAD0__FPv);
#ifdef SKIP_ASM
void* func_0035AAD0(void* self)
{
    void* t0 = (char*)*(void**)((char*)self + 0x34) + 0x1;
    *(int*)((char*)self + 0x34) = (int)t0;
    return t0;
}
#endif

//100%
INCLUDE_ASM("object/splinemodifier", func_0035AAE0__FPv);
#ifdef SKIP_ASM
void* func_0035AAE0(void* self)
{
    void* t0 = (char*)*(void**)((char*)self + 0x34) - 0x1;
    *(int*)((char*)self + 0x34) = (int)t0;
    return t0;
}
#endif

INCLUDE_ASM("object/splinemodifier", func_0035AAF0);

INCLUDE_ASM("object/splinemodifier", func_0035AB60);

INCLUDE_ASM("object/splinemodifier", func_0035ABF0);

INCLUDE_ASM("object/splinemodifier", func_0035AC20);

INCLUDE_ASM("object/splinemodifier", func_0035B200);

INCLUDE_ASM("object/splinemodifier", func_0035B418);

INCLUDE_ASM("object/splinemodifier", func_0035B5A8);

//100%
INCLUDE_ASM("object/splinemodifier", func_0035B670);
#ifdef SKIP_ASM
extern "C" void func_0035B670(void* self, void* node)
{
    void* h = *(void**)self;
    if (h != 0) {
        *(void**)((char*)h + 0x4) = node;
    }
    *(void**)((char*)node + 0x4) = self;
    *(void**)node = *(void**)self;
    *(void**)self = node;
}
#endif

INCLUDE_ASM("object/splinemodifier", func_0035B690);

INCLUDE_ASM("object/splinemodifier", func_0035B6D0);

INCLUDE_ASM("object/splinemodifier", func_0035B708);

INCLUDE_ASM("object/splinemodifier", func_0035BA88);

INCLUDE_ASM("object/splinemodifier", func_0035BD70);

INCLUDE_ASM("object/splinemodifier", func_0035C040);

