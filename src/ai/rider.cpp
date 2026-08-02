#include "common.h"

INCLUDE_ASM("ai/rider", cRider_cRider);

INCLUDE_ASM("ai/rider", func_0011B978);

INCLUDE_ASM("ai/rider", cRider_addFocusBox);

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* func_00117248(void* mem);
extern "C" void cRiderMetrix_linkToRider(void* metrix);
extern const char D_00457970[];

struct cRider {
    char pad_0x00[0x790];
    void* field_0x790;
};

//95%
INCLUDE_ASM("ai/rider", cRider_addRiderMetrix__FP6cRider);
#ifdef SKIP_ASM
void cRider_addRiderMetrix(cRider* self)
{
    void* mem = cMemMan_alloc(0x1CC, D_00457970, 0, 0);
    void* metrix = func_00117248(mem);
    self->field_0x790 = metrix;
    cRiderMetrix_linkToRider(metrix);
}
#endif

INCLUDE_ASM("ai/rider", func_0011BBE8);

INCLUDE_ASM("ai/rider", func_0011BD60);

INCLUDE_ASM("ai/rider", func_0011BE88);

INCLUDE_ASM("ai/rider", func_0011C0E0);

INCLUDE_ASM("ai/rider", func_0011C138);

INCLUDE_ASM("ai/rider", cRider_initOnce);

INCLUDE_ASM("ai/rider", func_0011C298);

INCLUDE_ASM("ai/rider", func_0011D390);

INCLUDE_ASM("ai/rider", func_0011D640);

INCLUDE_ASM("ai/rider", func_0011D660);

INCLUDE_ASM("ai/rider", func_0011DD98);

INCLUDE_ASM("ai/rider", func_0011DE60);

INCLUDE_ASM("ai/rider", func_0011DF18);

INCLUDE_ASM("ai/rider", func_0011DFE0);

INCLUDE_ASM("ai/rider", cRider_updateOrientationImplicit);

INCLUDE_ASM("ai/rider", func_0011E150);

INCLUDE_ASM("ai/rider", func_0011EB60);

INCLUDE_ASM("ai/rider", func_0011EB98);

INCLUDE_ASM("ai/rider", func_0011F3D8);

INCLUDE_ASM("ai/rider", cRider_doLeanPoseAdjust);

extern "C" void* func_001112B8(int);

//100%
INCLUDE_ASM("ai/rider", func_0011FE78__FPv);
#ifdef SKIP_ASM
void* func_0011FE78(void* self)
{
    return func_001112B8(*(int*)((char*)self + 0x77c));
}
#endif

//100%
INCLUDE_ASM("ai/rider", func_0011FE98__FPv);
#ifdef SKIP_ASM
int func_0011FE98(void* self)
{
    return *(int*)((char*)*(void**)((char*)self + 0x77c) + 0xde0);
}
#endif

extern "C" void* func_00111538(int);

//100%
INCLUDE_ASM("ai/rider", func_0011FEC8__FPv);
#ifdef SKIP_ASM
void* func_0011FEC8(void* self)
{
    return func_00111538(*(int*)((char*)self + 0x77c));
}
#endif

//100%
INCLUDE_ASM("ai/rider", func_0011FEE8__FPv);
#ifdef SKIP_ASM
int func_0011FEE8(void* self)
{
    return *(int*)((char*)*(void**)((char*)self + 0x77c) + 0xde4);
}
#endif

INCLUDE_ASM("ai/rider", func_0011FF48);

INCLUDE_ASM("ai/rider", cRider_getMass);

INCLUDE_ASM("ai/rider", func_00120038);

INCLUDE_ASM("ai/rider", func_00120090);

INCLUDE_ASM("ai/rider", func_001200D0);

INCLUDE_ASM("ai/rider", func_00120378);

INCLUDE_ASM("ai/rider", func_00120D58);

INCLUDE_ASM("ai/rider", func_00120D90);

INCLUDE_ASM("ai/rider", func_00120E30);

INCLUDE_ASM("ai/rider", func_00120E50);

INCLUDE_ASM("ai/rider", func_00120E88);

INCLUDE_ASM("ai/rider", func_00120ED8);

INCLUDE_ASM("ai/rider", func_00120F20);

INCLUDE_ASM("ai/rider", func_00121068);

INCLUDE_ASM("ai/rider", func_001210B0);

INCLUDE_ASM("ai/rider", func_001211F8);

extern "C" void* func_00111408(int);

//100%
INCLUDE_ASM("ai/rider", func_001216E0__FPv);
#ifdef SKIP_ASM
void* func_001216E0(void* self)
{
    return func_00111408(*(int*)((char*)self + 0x77c));
}
#endif

INCLUDE_ASM("ai/rider", func_00121700);

INCLUDE_ASM("ai/rider", func_00121728);

INCLUDE_ASM("ai/rider", func_00121750);

extern "C" void* func_003103F0(int);

//100%
INCLUDE_ASM("ai/rider", func_001217F8__FPv);
#ifdef SKIP_ASM
void* func_001217F8(void* self)
{
    return func_003103F0(*(int*)((char*)self + 0x780));
}
#endif

INCLUDE_ASM("ai/rider", func_00121818);

INCLUDE_ASM("ai/rider", func_001218D0);

INCLUDE_ASM("ai/rider", func_00121950);

INCLUDE_ASM("ai/rider", func_00121AA0);

INCLUDE_ASM("ai/rider", func_00121F30);

INCLUDE_ASM("ai/rider", func_00122088);

INCLUDE_ASM("ai/rider", func_001220D8);

INCLUDE_ASM("ai/rider", func_00122278);

INCLUDE_ASM("ai/rider", func_00122448);

INCLUDE_ASM("ai/rider", func_001225C0);

INCLUDE_ASM("ai/rider", func_001225F0);

extern "C" void* func_002F2088(int);

//100%
INCLUDE_ASM("ai/rider", func_00122638__FPv);
#ifdef SKIP_ASM
void* func_00122638(void* self)
{
    return func_002F2088(*(int*)((char*)self + 0x88c));
}
#endif

INCLUDE_ASM("ai/rider", func_00122658);

INCLUDE_ASM("ai/rider", func_00122898);

INCLUDE_ASM("ai/rider", func_00122C28);

INCLUDE_ASM("ai/rider", func_00122C98);

extern "C" void* func_001231A8(void* self);

//100%
INCLUDE_ASM("ai/rider", func_00122CD0__FPv);
#ifdef SKIP_ASM
void* func_00122CD0(void* self)
{
    return func_001231A8(self);
}
#endif

INCLUDE_ASM("ai/rider", func_00122CF0);

INCLUDE_ASM("ai/rider", func_00122D78);

INCLUDE_ASM("ai/rider", func_00122E50);

INCLUDE_ASM("ai/rider", func_00122EE8);

INCLUDE_ASM("ai/rider", func_00123128);

INCLUDE_ASM("ai/rider", func_00123168);

INCLUDE_ASM("ai/rider", func_001231A8);

INCLUDE_ASM("ai/rider", func_00123210);

INCLUDE_ASM("ai/rider", func_001234D0);

INCLUDE_ASM("ai/rider", func_001235F8);

INCLUDE_ASM("ai/rider", func_00123640);

INCLUDE_ASM("ai/rider", func_00123B48);

INCLUDE_ASM("ai/rider", func_00123DA8);

INCLUDE_ASM("ai/rider", func_00123E30);

INCLUDE_ASM("ai/rider", func_00123F38);

INCLUDE_ASM("ai/rider", func_001241C0);

INCLUDE_ASM("ai/rider", func_001242B0);

INCLUDE_ASM("ai/rider", func_00124788);

INCLUDE_ASM("ai/rider", func_00125038);

INCLUDE_ASM("ai/rider", func_001250A8);

INCLUDE_ASM("ai/rider", func_00125108);

INCLUDE_ASM("ai/rider", func_00125228);

INCLUDE_ASM("ai/rider", cRider_quitEvent);

INCLUDE_ASM("ai/rider", func_00125448);

INCLUDE_ASM("ai/rider", func_00125958);

INCLUDE_ASM("ai/rider", func_00125970);

//100%
INCLUDE_ASM("ai/rider", func_00125AD0__FPv);
#ifdef SKIP_ASM
void func_00125AD0(void* self)
{
}
#endif

INCLUDE_ASM("ai/rider", func_00125AD8);

INCLUDE_ASM("ai/rider", func_00125B18);

INCLUDE_ASM("ai/rider", func_00125C70);

INCLUDE_ASM("ai/rider", func_00125EB8);

INCLUDE_ASM("ai/rider", func_001276F0);

INCLUDE_ASM("ai/rider", func_00127848);

//99.33%
INCLUDE_ASM("ai/rider", func_001278C0__FPv);
#ifdef SKIP_ASM
void func_001278C0(void* self)
{
    int t0 = 0;
    *(int*)((char*)self + 0xdfc) = t0;
    *(int*)((char*)self + 0xe00) = t0;
}
#endif

INCLUDE_ASM("ai/rider", func_001278D0);

//100%
INCLUDE_ASM("ai/rider", func_001278E0__FPvf);
#ifdef SKIP_ASM
void func_001278E0(void* self, float val)
{
    *(float*)((char*)self + 0xE00) = val;
}
#endif

INCLUDE_ASM("ai/rider", func_001278E8);

INCLUDE_ASM("ai/rider", func_00127998);

extern "C" void* func_00111AC0(void* self);

//100%
INCLUDE_ASM("ai/rider", func_00128660__FPv);
#ifdef SKIP_ASM
void* func_00128660(void* self)
{
    return func_00111AC0(self);
}
#endif

extern "C" void* func_00111D98(void* self);

//100%
INCLUDE_ASM("ai/rider", func_00128680__FPv);
#ifdef SKIP_ASM
void* func_00128680(void* self)
{
    return func_00111D98(self);
}
#endif

