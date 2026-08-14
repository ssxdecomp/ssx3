#include "common.h"

// R5900 128-bit GPR quadword, for functions that copy a 16-byte block via a
// single lq/sq pair instead of word-by-word.
typedef int cQuad128 __attribute__((mode(TI)));

INCLUDE_ASM("render/graphicsman", cGraphicsMan_AddBlendedMatrix);

INCLUDE_ASM("render/graphicsman", func_00369A78);

INCLUDE_ASM("render/graphicsman", func_00369C28);

INCLUDE_ASM("render/graphicsman", func_00369CB0);

INCLUDE_ASM("render/graphicsman", func_00369CF8);

//100%
INCLUDE_ASM("render/graphicsman", func_00369FF0__FPv);
#ifdef SKIP_ASM
void func_00369FF0(void* self)
{
}
#endif

INCLUDE_ASM("render/graphicsman", func_00369FF8);

INCLUDE_ASM("render/graphicsman", func_0036A020);

INCLUDE_ASM("render/graphicsman", func_0036A048);

extern "C" void* func_0036A1C0(int);

//100%
INCLUDE_ASM("render/graphicsman", func_0036A190__FPvi);
#ifdef SKIP_ASM
void* func_0036A190(void* self, int a1)
{
    return func_0036A1C0(a1);
}
#endif

//100%
INCLUDE_ASM("render/graphicsman", func_0036A1B0__FPvT0);
#ifdef SKIP_ASM
int func_0036A1B0(void* self, void* a1)
{
    int t0 = -1;
    *(int*)a1 = 0;
    *(int*)((char*)a1 + 0x4) = t0;
    return t0;
}
#endif

INCLUDE_ASM("render/graphicsman", func_0036A1C0);

INCLUDE_ASM("render/graphicsman", func_0036A1E8);

INCLUDE_ASM("render/graphicsman", func_0036A290);

INCLUDE_ASM("render/graphicsman", func_0036A2C0);

INCLUDE_ASM("render/graphicsman", func_0036A428);

INCLUDE_ASM("render/graphicsman", func_0036AA60);

INCLUDE_ASM("render/graphicsman", func_0036ABA0);

INCLUDE_ASM("render/graphicsman", func_0036AC00);

INCLUDE_ASM("render/graphicsman", func_0036AE20);

INCLUDE_ASM("render/graphicsman", func_0036B158);

INCLUDE_ASM("render/graphicsman", func_0036B9D8);

INCLUDE_ASM("render/graphicsman", func_0036C188);

INCLUDE_ASM("render/graphicsman", func_0036C398);

INCLUDE_ASM("render/graphicsman", func_0036C740);

INCLUDE_ASM("render/graphicsman", func_0036C790);

INCLUDE_ASM("render/graphicsman", func_0036CBF8);

INCLUDE_ASM("render/graphicsman", func_0036CCB8);

INCLUDE_ASM("render/graphicsman", func_0036CE00);

//100%
INCLUDE_ASM("render/graphicsman", func_0036CE28);
#ifdef SKIP_ASM
extern "C" void func_0036CE28(void* self, float a, float b)
{
    float d = b - a;
    float s = *(float*)((char*)self + 0x4c);
    a = a * s;
    d = d * s;
    *(float*)((char*)self + 0x14) = d;
    *(float*)((char*)self + 0x1c) = a - d;
}
#endif

INCLUDE_ASM("render/graphicsman", func_0036CEF8);

extern cQuad128 D_004FF120;

//100%
INCLUDE_ASM("render/graphicsman", func_0036D008);
#ifdef SKIP_ASM
extern "C" void func_0036D008(void* self)
{
    *(cQuad128*)((char*)self + 0xe0) = D_004FF120;
}
#endif

INCLUDE_ASM("render/graphicsman", func_0036D1F0);

INCLUDE_ASM("render/graphicsman", func_0036D318);

//100%
INCLUDE_ASM("render/graphicsman", func_0036D3D8);
#ifdef SKIP_ASM
extern "C" void func_0036D3D8(void* self, float val)
{
    *(float*)((char*)self + 0x8) = val * *(float*)((char*)self + 0x4c);
}
#endif

//100%
INCLUDE_ASM("render/graphicsman", func_0036D3E8);
#ifdef SKIP_ASM
extern "C" void func_0036D3E8(void* self, float val)
{
    *(float*)((char*)self + 0x8) += val * *(float*)((char*)self + 0x4c);
}
#endif

INCLUDE_ASM("render/graphicsman", func_0036D400);

INCLUDE_ASM("render/graphicsman", func_0036D428);

INCLUDE_ASM("render/graphicsman", func_0036D500);

INCLUDE_ASM("render/graphicsman", func_00370018);

INCLUDE_ASM("render/graphicsman", func_00370058);

INCLUDE_ASM("render/graphicsman", func_003705E0);

INCLUDE_ASM("render/graphicsman", func_00370758);

INCLUDE_ASM("render/graphicsman", func_00370788);

INCLUDE_ASM("render/graphicsman", func_00370888);

INCLUDE_ASM("render/graphicsman", func_003708C0);

INCLUDE_ASM("render/graphicsman", func_00370AA8);

INCLUDE_ASM("render/graphicsman", func_00370AF8);

INCLUDE_ASM("render/graphicsman", func_00370B60);

INCLUDE_ASM("render/graphicsman", func_00370C08);

