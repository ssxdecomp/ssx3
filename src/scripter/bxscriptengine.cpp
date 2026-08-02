#include "common.h"

INCLUDE_ASM("scripter/bxscriptengine", cBXScriptEngine_SetupBXEngine);

INCLUDE_ASM("scripter/bxscriptengine", func_00282020);

INCLUDE_ASM("scripter/bxscriptengine", func_002820B0);

INCLUDE_ASM("scripter/bxscriptengine", func_00282150);

INCLUDE_ASM("scripter/bxscriptengine", func_00282178);

INCLUDE_ASM("scripter/bxscriptengine", func_002821A0);

INCLUDE_ASM("scripter/bxscriptengine", func_002822A0);

INCLUDE_ASM("scripter/bxscriptengine", func_00282338);

INCLUDE_ASM("scripter/bxscriptengine", func_00282390);

INCLUDE_ASM("scripter/bxscriptengine", func_002823F0);

INCLUDE_ASM("scripter/bxscriptengine", func_00282450);

INCLUDE_ASM("scripter/bxscriptengine", func_00282540);

INCLUDE_ASM("scripter/bxscriptengine", func_002826D8);

INCLUDE_ASM("scripter/bxscriptengine", func_00282720);

INCLUDE_ASM("scripter/bxscriptengine", func_00282798);

INCLUDE_ASM("scripter/bxscriptengine", func_00282838);

INCLUDE_ASM("scripter/bxscriptengine", func_002828B8);

INCLUDE_ASM("scripter/bxscriptengine", func_00282908);

INCLUDE_ASM("scripter/bxscriptengine", func_002829D0);

INCLUDE_ASM("scripter/bxscriptengine", func_00282A18);

INCLUDE_ASM("scripter/bxscriptengine", func_00282A80);

INCLUDE_ASM("scripter/bxscriptengine", func_00282B40);

INCLUDE_ASM("scripter/bxscriptengine", func_00282B88);

//100%
INCLUDE_ASM("scripter/bxscriptengine", func_00282BB0__FPvT0);
#ifdef SKIP_ASM
int func_00282BB0(void* self, void* a1)
{
    return *(int*)((char*)*(void**)((char*)a1 + 0xc) + 0xc);
}
#endif

//100%
INCLUDE_ASM("scripter/bxscriptengine", func_00282BE0__FPvT0);
#ifdef SKIP_ASM
int func_00282BE0(void* self, void* a1)
{
    return *(int*)((char*)*(void**)((char*)a1 + 0xc) + 0x1c);
}
#endif

INCLUDE_ASM("scripter/bxscriptengine", func_00282BF0);

extern "C" void* func_00272CC0(int);

//100%
INCLUDE_ASM("scripter/bxscriptengine", func_00282C18__FPv);
#ifdef SKIP_ASM
void* func_00282C18(void* self)
{
    return func_00272CC0(*(int*)((char*)self + 0x2b8));
}
#endif

INCLUDE_ASM("scripter/bxscriptengine", func_00282C38);

//87.5%
INCLUDE_ASM("scripter/bxscriptengine", func_00282C88__FPvT0);
#ifdef SKIP_ASM
int func_00282C88(void* self, void* a1)
{
    int t0 = 0;
    int t1 = -1;
    *(int*)((char*)a1 + 0xc) = t0;
    *(int*)((char*)a1 + 0x14) = t1;
    *(int*)a1 = t0;
    *(int*)((char*)a1 + 0x4) = t0;
    *(int*)((char*)a1 + 0x20) = t0;
    *(short*)((char*)a1 + 0x10) = (short)t0;
    *(short*)((char*)a1 + 0x12) = (short)t0;
    *(int*)((char*)a1 + 0x18) = t0;
    return t1;
}
#endif

INCLUDE_ASM("scripter/bxscriptengine", func_00282CB0);

INCLUDE_ASM("scripter/bxscriptengine", func_00282CD0);

INCLUDE_ASM("scripter/bxscriptengine", func_00282D30);

//100%
INCLUDE_ASM("scripter/bxscriptengine", func_00282DA8__FPvi);
#ifdef SKIP_ASM
void func_00282DA8(void* self, int val)
{
    *(int*)((char*)self + 0x10) = val;
}
#endif

extern "C" void* func_00282DD0(void*, int, int, int);

//100%
INCLUDE_ASM("scripter/bxscriptengine", func_00282DB0__FPvii);
#ifdef SKIP_ASM
void* func_00282DB0(void* self, int a1, int a2)
{
    return func_00282DD0(self, a1, a2, *(int*)((char*)self + 0x28));
}
#endif

INCLUDE_ASM("scripter/bxscriptengine", func_00282DD0);

INCLUDE_ASM("scripter/bxscriptengine", func_00282EF0);

INCLUDE_ASM("scripter/bxscriptengine", func_00282F00);

INCLUDE_ASM("scripter/bxscriptengine", func_00282F30);

INCLUDE_ASM("scripter/bxscriptengine", func_00282F60);

//100%
INCLUDE_ASM("scripter/bxscriptengine", func_00282F80__FPv);
#ifdef SKIP_ASM
int func_00282F80(void* self)
{
    return (*(int*)((char*)self + 0x8) != 0);
}
#endif

INCLUDE_ASM("scripter/bxscriptengine", func_00282F90);

INCLUDE_ASM("scripter/bxscriptengine", func_00282FB8);

INCLUDE_ASM("scripter/bxscriptengine", func_00283000);

INCLUDE_ASM("scripter/bxscriptengine", func_00283038);

INCLUDE_ASM("scripter/bxscriptengine", func_00283060);

INCLUDE_ASM("scripter/bxscriptengine", func_00283088);

INCLUDE_ASM("scripter/bxscriptengine", func_002830C8);

INCLUDE_ASM("scripter/bxscriptengine", func_00283180);

INCLUDE_ASM("scripter/bxscriptengine", func_002831B0);

INCLUDE_ASM("scripter/bxscriptengine", func_00283200);

INCLUDE_ASM("scripter/bxscriptengine", func_00283228);

INCLUDE_ASM("scripter/bxscriptengine", func_00283298);

INCLUDE_ASM("scripter/bxscriptengine", func_002832D8);

INCLUDE_ASM("scripter/bxscriptengine", func_00283320);

INCLUDE_ASM("scripter/bxscriptengine", func_002833A8);

//100%
INCLUDE_ASM("scripter/bxscriptengine", func_00283430__FPv);
#ifdef SKIP_ASM
void* func_00283430(void* self)
{
    void* t0 = (char*)*(void**)((char*)self + 0x8) + 0x1;
    *(int*)((char*)self + 0x8) = (int)t0;
    return t0;
}
#endif

//100%
INCLUDE_ASM("scripter/bxscriptengine", func_00283440__FPv);
#ifdef SKIP_ASM
void* func_00283440(void* self)
{
    void* t0 = (char*)*(void**)((char*)self + 0x8) - 0x1;
    *(int*)((char*)self + 0x8) = (int)t0;
    return t0;
}
#endif

