#include "common.h"

struct cOVStateHUDElem {
    int field_0x0;
    int field_0x4;
    float rangeMin; // 0x8
    float rangeMax; // 0xc
    float x; // 0x10
    float y; // 0x14
    float z; // 0x18
    float w; // 0x1c
};

INCLUDE_ASM("fe/ovstatehud", cOVStateHiScoreList_onCreateScreen);

INCLUDE_ASM("fe/ovstatehud", func_001E9130);

//64.67%
INCLUDE_ASM("fe/ovstatehud", func_001E91A8__FPvT0);
#ifdef SKIP_ASM
float func_001E91A8(void* self, void* a1)
{
    cOVStateHUDElem* e = (cOVStateHUDElem*)self;
    float t0 = e->z;
    *(float*)a1 = e->x;
    *(float*)((char*)a1 + 0x4) = e->y;
    *(float*)((char*)a1 + 0x8) = t0;
    *(float*)((char*)a1 + 0xc) = e->w;
    return t0;
}
#endif

//64.67%
INCLUDE_ASM("fe/ovstatehud", func_001E91D0__FPvT0);
#ifdef SKIP_ASM
float func_001E91D0(void* self, void* a1)
{
    cOVStateHUDElem* e = (cOVStateHUDElem*)self;
    float t0 = e->z;
    *(float*)((char*)a1 + 0xc) = e->x;
    *(float*)a1 = e->y;
    *(float*)((char*)a1 + 0x4) = t0;
    *(float*)((char*)a1 + 0x8) = e->w;
    return t0;
}
#endif

INCLUDE_ASM("fe/ovstatehud", func_001E91F8);

INCLUDE_ASM("fe/ovstatehud", func_001E9220);

//100%
INCLUDE_ASM("fe/ovstatehud", func_001E9290__FPvT0);
#ifdef SKIP_ASM
float func_001E9290(void* self, void* a1)
{
    cOVStateHUDElem* e = (cOVStateHUDElem*)self;
    float t0 = e->rangeMin;
    *(float*)a1 = t0;
    *(float*)((char*)a1 + 0x4) = e->rangeMax;
    return t0;
}
#endif

INCLUDE_ASM("fe/ovstatehud", func_001E92A8);

INCLUDE_ASM("fe/ovstatehud", func_001E94E0);

INCLUDE_ASM("fe/ovstatehud", func_001E9540);

INCLUDE_ASM("fe/ovstatehud", func_001E95A0);

INCLUDE_ASM("fe/ovstatehud", func_001E9A30);

INCLUDE_ASM("fe/ovstatehud", cOVStateHUD1P_onCreateScreen);

INCLUDE_ASM("fe/ovstatehud", func_001EA930);

INCLUDE_ASM("fe/ovstatehud", func_001EC1F0);

INCLUDE_ASM("fe/ovstatehud", cOVStateHUD1P_onRender2D);

INCLUDE_ASM("fe/ovstatehud", func_001F10F8);

INCLUDE_ASM("fe/ovstatehud", func_001F1190);

INCLUDE_ASM("fe/ovstatehud", func_001F1338);

INCLUDE_ASM("fe/ovstatehud", func_001F14B0);

INCLUDE_ASM("fe/ovstatehud", func_001F16C0);

INCLUDE_ASM("fe/ovstatehud", cOVStateHUD1P_renderTime);

INCLUDE_ASM("fe/ovstatehud", func_001F1B30);

INCLUDE_ASM("fe/ovstatehud", func_001F1E28);

INCLUDE_ASM("fe/ovstatehud", func_001F22E8);

INCLUDE_ASM("fe/ovstatehud", func_001F2AA0);

INCLUDE_ASM("fe/ovstatehud", func_001F2DB0);

//100%
INCLUDE_ASM("fe/ovstatehud", func_001F30C0__FPv);
#ifdef SKIP_ASM
void* func_001F30C0(void* self)
{
    cOVStateHUDElem* e = (cOVStateHUDElem*)self;
    int t0 = 0;
    e->field_0x0 = t0;
    *(int*)&e->rangeMax = t0;
    e->field_0x4 = t0;
    *(int*)&e->rangeMin = t0;
    return self;
}
#endif

INCLUDE_ASM("fe/ovstatehud", func_001F30D8);

//99.2%
INCLUDE_ASM("fe/ovstatehud", func_001F3170__FPv);
#ifdef SKIP_ASM
void func_001F3170(void* self)
{
    cOVStateHUDElem* e = (cOVStateHUDElem*)self;
    int t0 = 0;
    *(int*)&e->rangeMin = t0;
    e->field_0x0 = t0;
    *(int*)&e->rangeMax = t0;
    e->field_0x4 = t0;
}
#endif

INCLUDE_ASM("fe/ovstatehud", func_001F3188);

INCLUDE_ASM("fe/ovstatehud", func_001F31E0);

//100%
INCLUDE_ASM("fe/ovstatehud", func_001F36C0);
#ifdef SKIP_ASM
extern "C" void func_001F36C0(void* self, int bit)
{
    *(int*)((char*)self + 0x4) |= (1 << bit);
}
#endif

INCLUDE_ASM("fe/ovstatehud", func_001F36D8);

INCLUDE_ASM("fe/ovstatehud", func_001F3700);

