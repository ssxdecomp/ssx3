#include "common.h"

// R5900 128-bit GPR quadword, for functions that copy a 16-byte block via a
// single lq/sq pair instead of word-by-word.
typedef int cQuad128 __attribute__((mode(TI)));

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

struct cQuat {
    float x, y, z, w;
} __attribute__((aligned(16)));

extern "C" void func_0031BE50(float angle, float* s, float* c);
extern "C" void cRider_updateOrientationImplicit(void* self);

// Pre-multiplies the physical quaternion (+0x120) by a rotation of `angle`
// about `axis` (not normalised here), then rebuilds the orientation.
//85.52%
INCLUDE_ASM("ai/rider", func_0011DFE0);
#ifdef SKIP_ASM
extern "C" void func_0011DFE0(void* self, float* axis, float angle)
{
    cQuat t;
    cQuat q;
    cQuat r;
    float s;
    float c;

    func_0031BE50(angle * 0.5f, &s, &c);
    q.x = s * axis[0];
    q.y = s * axis[1];
    q.z = s * axis[2];
    q.w = c;
    __asm__ volatile(
        ".set noreorder\n"
        "lqc2       $vf4, %1\n"
        "lqc2       $vf5, %2\n"
        "vmul.xyzw  $vf7, $vf4, $vf5\n"
        "vopmula.xyz ACC, $vf4, $vf5\n"
        "vopmsub.xyz $vf6, $vf5, $vf4\n"
        "vmulaw.xyz ACC, $vf4, $vf5w\n"
        "vmaddaw.xyz ACC, $vf5, $vf4w\n"
        "vsubax.w   ACC, $vf7, $vf7x\n"
        "vmsubay.w  ACC, $vf0, $vf7y\n"
        "vmsubz.w   $vf8, $vf0, $vf7z\n"
        "vmaddw.xyz $vf8, $vf6, $vf0w\n"
        "sqc2       $vf8, %0\n"
        ".set reorder\n"
        : "=m"(r)
        : "m"(q), "m"(*(cQuat*)((char*)self + 0x120)));
    *(cQuat*)((char*)self + 0x120) = t = r;
    cRider_updateOrientationImplicit(self);
}
#endif

//100%
INCLUDE_ASM("ai/rider", cRider_updateOrientationImplicit);
#ifdef SKIP_ASM
// Normalises the physical quaternion (+0x120) and rebuilds the orientation
// matrix at +0x1A0 (rows right/forward/up, position +0x110 as row 3), VU0.
extern "C" void cRider_updateOrientationImplicit(void* self)
{
    __asm__ volatile(
        ".set noreorder\n"
        "lqc2       $vf3, %1\n"
        "vaddw.x    $vf6, $vf0, $vf0w\n"
        "vmul.xyzw  $vf4, $vf3, $vf3\n"
        "vadday.x   ACC, $vf4, $vf4y\n"
        "vmaddaz.x  ACC, $vf6, $vf4z\n"
        "vmaddw.x   $vf4, $vf6, $vf4w\n"
        "vrsqrt     Q, $vf0w, $vf4x\n"
        "vwaitq\n"
        "vmulq.xyzw $vf5, $vf3, Q\n"
        "sqc2       $vf5, %1\n"
        "lqc2       $vf4, %1\n"
        "lqc2       $vf3, %2\n"
        "vaddw.xyz  $vf1, $vf0, $vf0w\n"
        "vadd.xyz   $vf5, $vf4, $vf4\n"
        "vsub.w     $vf10, $vf10, $vf10\n"
        "vsub.w     $vf11, $vf11, $vf11\n"
        "vsub.w     $vf12, $vf12, $vf12\n"
        "vmul.xyz   $vf6, $vf5, $vf4\n"
        "vmulw.xyz  $vf7, $vf5, $vf4w\n"
        "vopmula.xyz ACC, $vf5, $vf4\n"
        "vmadd.xyz  $vf8, $vf0, $vf0\n"
        "vsubay.x   ACC, $vf1, $vf6y\n"
        "vmsubz.x   $vf10, $vf1, $vf6z\n"
        "vsubaz.y   ACC, $vf1, $vf6z\n"
        "vmsubx.y   $vf11, $vf1, $vf6x\n"
        "vsubax.z   ACC, $vf1, $vf6x\n"
        "vmsuby.z   $vf12, $vf1, $vf6y\n"
        "vaddaz.y   ACC, $vf0, $vf8z\n"
        "vmaddz.y   $vf10, $vf1, $vf7z\n"
        "vaddax.z   ACC, $vf0, $vf8x\n"
        "vmaddx.z   $vf11, $vf1, $vf7x\n"
        "vaddax.y   ACC, $vf0, $vf8x\n"
        "vmsubx.y   $vf12, $vf1, $vf7x\n"
        "vadday.z   ACC, $vf0, $vf8y\n"
        "vmsuby.z   $vf10, $vf1, $vf7y\n"
        "vaddaz.x   ACC, $vf0, $vf8z\n"
        "vmsubz.x   $vf11, $vf1, $vf7z\n"
        "vadday.x   ACC, $vf0, $vf8y\n"
        "vmaddy.x   $vf12, $vf1, $vf7y\n"
        "sqc2       $vf3, 0x30(%0)\n"
        "sqc2       $vf10, 0x0(%0)\n"
        "sqc2       $vf11, 0x10(%0)\n"
        "sqc2       $vf12, 0x20(%0)\n"
        ".set reorder\n"
        :
        : "r"((char*)self + 0x1a0), "m"(*(cQuad128*)((char*)self + 0x120)), "m"(*(cQuad128*)((char*)self + 0x110))
        : "memory");
}
#endif

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

//100%
INCLUDE_ASM("ai/rider", func_0011FF48);
#ifdef SKIP_ASM
// 0x20-byte elements with the quadword at offset 0
struct sRiderXform {
    cQuad128 q;
    char pad_0x10[0x10];
};

extern "C" void* func_0011FF48(void* dst, void* self)
{
    void* q = *(void**)((char*)self + 0x780);
    int i = *(int*)((char*)self + 0x89c);
    sRiderXform* b = *(sRiderXform**)((char*)q + 0x2c);
    *(cQuad128*)dst = b[i].q;
    return dst;
}
#endif

extern "C" void* cBE_getBE();
void* cBE_getInterface(void* be, int kind);
int cBECharacterInterface_getWeight(void* iface, int character);
extern "C" float cBEStatInterface_getCollisionAttrib(void* iface, int character, int stat);

//100%
INCLUDE_ASM("ai/rider", cRider_getMass);
#ifdef SKIP_ASM
extern "C" float cRider_getMass(void* self)
{
    int weight = cBECharacterInterface_getWeight(cBE_getInterface(cBE_getBE(), 2), *(int*)((char*)self + 0x86c));
    float toughness = cBEStatInterface_getCollisionAttrib(cBE_getInterface(cBE_getBE(), 3),
                                                          *(int*)((char*)self + 0x86c), *(int*)((char*)self + 0xb34));

    return (float)weight * (toughness * 1.5003352165222168f + 1.0f) * (*(float*)((char*)self + 0x2fc) * 10.0f + 1.0f);
}
#endif

extern "C" float func_00149690(void* iface, int character, int stat);

// Grab playback speed: 1 + grab stat * 0.2998.
//100%
INCLUDE_ASM("ai/rider", func_00120038);
#ifdef SKIP_ASM
extern "C" float func_00120038(void* self)
{
    void* iface = cBE_getInterface(cBE_getBE(), 3);
    return func_00149690(iface, *(int*)((char*)self + 0x86c), *(int*)((char*)self + 0xb34)) * 0.29988324642181396f + 1.0f;
}
#endif

INCLUDE_ASM("ai/rider", func_00120090);

INCLUDE_ASM("ai/rider", func_001200D0);

INCLUDE_ASM("ai/rider", func_00120378);

INCLUDE_ASM("ai/rider", func_00120D58);

INCLUDE_ASM("ai/rider", func_00120D90);

//100%
INCLUDE_ASM("ai/rider", func_00120E30);
#ifdef SKIP_ASM
extern "C" void func_00120E30(void* self)
{
    void* p = *(void**)((char*)self + 0x78c);
    if (p != 0) {
        *(cQuad128*)p = *(cQuad128*)((char*)self + 0x110);
    }
}
#endif

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

extern "C" int func_001231A8(void* self);

//100%
INCLUDE_ASM("ai/rider", func_00122CD0__FPv);
#ifdef SKIP_ASM
void* func_00122CD0(void* self)
{
    return (void*)func_001231A8(self);
}
#endif

INCLUDE_ASM("ai/rider", func_00122CF0);

INCLUDE_ASM("ai/rider", func_00122D78);

INCLUDE_ASM("ai/rider", func_00122E50);

INCLUDE_ASM("ai/rider", func_00122EE8);

INCLUDE_ASM("ai/rider", func_00123128);

INCLUDE_ASM("ai/rider", func_00123168);

// Grounded predicate: motion 0, or motion 2 with owner+0x30 == 0.
//100%
INCLUDE_ASM("ai/rider", func_001231A8);
#ifdef SKIP_ASM
extern "C" int func_001231A8(void* self)
{
    int grounded = 0;

    if (func_0011FE98(self) == 0 ||
        (func_0011FE98(self) == 2 && *(int*)((char*)*(void**)((char*)self + 0x77c) + 0x30) == 0)) {
        grounded = 1;
    }
    return grounded;
}
#endif

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

//100%
INCLUDE_ASM("ai/rider", func_00125958);
#ifdef SKIP_ASM
extern "C" void func_00125958(void* self, int a1)
{
    *(int*)((char*)self + 0xb2c) = a1;
    if (a1 == 0) {
        *(int*)((char*)self + 0x2f4) = 0;
        *(int*)((char*)self + 0x2f0) = 0;
    }
}
#endif

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

