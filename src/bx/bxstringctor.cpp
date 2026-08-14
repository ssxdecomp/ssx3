#include "common.h"

extern void* D_004A3E90;

struct cBXString2 {
    void* field_0x0;
    void* field_0x4;
    void* field_0x8;
    void* field_0xC;
    void* field_0x10;
    void* arr[4]; // 0x14-0x23
};

//85.05% - loop shape (down-counting bne vs ours) not fully reproduced
INCLUDE_ASM("bx/bxstringctor", cBXString_cBXString__FP10cBXString2);
#ifdef SKIP_ASM
cBXString2* cBXString_cBXString(cBXString2* self)
{
    self->field_0x0 = D_004A3E90;
    self->field_0x4 = D_004A3E90;
    self->field_0x8 = D_004A3E90;
    self->field_0xC = D_004A3E90;
    self->field_0x10 = D_004A3E90;
    for (int i = 0; i < 4; i++) {
        self->arr[i] = D_004A3E90;
    }
    return self;
}
#endif

INCLUDE_ASM("bx/bxstringctor", func_00268950);

INCLUDE_ASM("bx/bxstringctor", func_002689B8);

// padded past the 8-byte gp-relative threshold so the compiler emits
// absolute lui/lo addressing like the target
struct sShortPad16 { short v; int pad[3]; };
extern sShortPad16 D_004A2FB0;
extern "C" void func_0025D6C0(int);

//100%
INCLUDE_ASM("bx/bxstringctor", func_00268A90);
#ifdef SKIP_ASM
extern "C" void func_00268A90(void* self, void* a1, int a2)
{
    func_0025D6C0(a2 + D_004A2FB0.v);
}
#endif

extern sShortPad16 D_004A2FB8;
extern "C" void func_002599B0(int);

//100%
INCLUDE_ASM("bx/bxstringctor", func_00268AB8);
#ifdef SKIP_ASM
extern "C" void func_00268AB8(void* self, void* a1, int a2)
{
    func_002599B0(a2 + D_004A2FB8.v);
}
#endif

INCLUDE_ASM("bx/bxstringctor", func_00268AE0);

INCLUDE_ASM("bx/bxstringctor", func_00268B08);

INCLUDE_ASM("bx/bxstringctor", func_00268B30);

INCLUDE_ASM("bx/bxstringctor", func_00268B58);

INCLUDE_ASM("bx/bxstringctor", func_00268B80);

INCLUDE_ASM("bx/bxstringctor", func_00268BA8);

INCLUDE_ASM("bx/bxstringctor", func_00268BD0);

INCLUDE_ASM("bx/bxstringctor", func_00268BF8);

INCLUDE_ASM("bx/bxstringctor", func_00268C20);

INCLUDE_ASM("bx/bxstringctor", func_00268C48);

INCLUDE_ASM("bx/bxstringctor", func_00268C70);

INCLUDE_ASM("bx/bxstringctor", func_00268C98);

INCLUDE_ASM("bx/bxstringctor", func_00268CC0);

INCLUDE_ASM("bx/bxstringctor", func_00268CE8);

INCLUDE_ASM("bx/bxstringctor", func_00268D10);

INCLUDE_ASM("bx/bxstringctor", func_00268D38);

INCLUDE_ASM("bx/bxstringctor", func_00268D60);

INCLUDE_ASM("bx/bxstringctor", func_00268D88);

INCLUDE_ASM("bx/bxstringctor", func_00268DB0);

INCLUDE_ASM("bx/bxstringctor", func_00268DD8);

INCLUDE_ASM("bx/bxstringctor", func_00268E00);

INCLUDE_ASM("bx/bxstringctor", func_00268E28);

INCLUDE_ASM("bx/bxstringctor", func_00268E78);

INCLUDE_ASM("bx/bxstringctor", func_00268EA0);

INCLUDE_ASM("bx/bxstringctor", func_00268EC8);

INCLUDE_ASM("bx/bxstringctor", func_00268EF0);

INCLUDE_ASM("bx/bxstringctor", func_00268F18);

INCLUDE_ASM("bx/bxstringctor", func_00268F40);

INCLUDE_ASM("bx/bxstringctor", func_00268F68);

INCLUDE_ASM("bx/bxstringctor", func_00268F90);

INCLUDE_ASM("bx/bxstringctor", func_00268FB8);

INCLUDE_ASM("bx/bxstringctor", func_00268FE0);

INCLUDE_ASM("bx/bxstringctor", func_00269008);

INCLUDE_ASM("bx/bxstringctor", func_002690C8);

INCLUDE_ASM("bx/bxstringctor", func_00269188);

INCLUDE_ASM("bx/bxstringctor", func_00269240);

INCLUDE_ASM("bx/bxstringctor", func_00269300);

INCLUDE_ASM("bx/bxstringctor", func_002693C0);

INCLUDE_ASM("bx/bxstringctor", func_00269478);

INCLUDE_ASM("bx/bxstringctor", func_00269538);

INCLUDE_ASM("bx/bxstringctor", func_00269608);

INCLUDE_ASM("bx/bxstringctor", func_002696F8);

INCLUDE_ASM("bx/bxstringctor", func_002697D0);

INCLUDE_ASM("bx/bxstringctor", func_00269890);

INCLUDE_ASM("bx/bxstringctor", func_00269948);

INCLUDE_ASM("bx/bxstringctor", func_00269A18);

INCLUDE_ASM("bx/bxstringctor", func_00269AE0);

INCLUDE_ASM("bx/bxstringctor", func_00269B90);

INCLUDE_ASM("bx/bxstringctor", func_00269C40);

INCLUDE_ASM("bx/bxstringctor", func_00269CF0);

extern "C" void* func_00267E18(void* self);

//100%
INCLUDE_ASM("bx/bxstringctor", func_00269DA0__FPv);
#ifdef SKIP_ASM
void* func_00269DA0(void* self)
{
    return func_00267E18(self);
}
#endif

INCLUDE_ASM("bx/bxstringctor", func_00269DC0);

//100%
INCLUDE_ASM("bx/bxstringctor", func_00269E20__FPv);
#ifdef SKIP_ASM
void* func_00269E20(void* self)
{
    return func_00267E18(self);
}
#endif

INCLUDE_ASM("bx/bxstringctor", func_00269E40);

extern "C" void* func_00267468(int, int);

//100%
INCLUDE_ASM("bx/bxstringctor", func_00269EA0__FPv);
#ifdef SKIP_ASM
void* func_00269EA0(void* self)
{
    return func_00267468(1, 0xffff);
}
#endif

//100%
INCLUDE_ASM("bx/bxstringctor", func_00269EC0__FPv);
#ifdef SKIP_ASM
int func_00269EC0(void* self)
{
    int t0 = 0x2e;
    *(int*)((char*)self + 0x38) = t0;
    *(int*)((char*)self + 0x3c) = 1;
    return t0;
}
#endif

INCLUDE_ASM("bx/bxstringctor", func_00269ED8);

INCLUDE_ASM("bx/bxstringctor", func_00269F18);

//100%
INCLUDE_ASM("bx/bxstringctor", func_0026A068__FPv);
#ifdef SKIP_ASM
void func_0026A068(void* self)
{
    *(int*)((char*)self + 0x38) = 0;
}
#endif

extern "C" void func_0026BA88(void*);

//100%
INCLUDE_ASM("bx/bxstringctor", func_0026A070);
#ifdef SKIP_ASM
extern "C" void func_0026A070(void* self, int a1, int a2)
{
    if (a2 == 0) {
        func_0026BA88((char*)self + 0x38);
    }
}
#endif

INCLUDE_ASM("bx/bxstringctor", func_0026A090);

INCLUDE_ASM("bx/bxstringctor", func_0026A0B8);

INCLUDE_ASM("bx/bxstringctor", func_0026A180);

INCLUDE_ASM("bx/bxstringctor", func_0026A338);

INCLUDE_ASM("bx/bxstringctor", func_0026A378);

INCLUDE_ASM("bx/bxstringctor", func_0026A428);

INCLUDE_ASM("bx/bxstringctor", func_0026A638);

INCLUDE_ASM("bx/bxstringctor", func_0026A8B8);

INCLUDE_ASM("bx/bxstringctor", func_0026A9B0);

INCLUDE_ASM("bx/bxstringctor", func_0026AA80);

INCLUDE_ASM("bx/bxstringctor", func_0026AB20);

INCLUDE_ASM("bx/bxstringctor", func_0026AC48);

INCLUDE_ASM("bx/bxstringctor", func_0026AC88);

INCLUDE_ASM("bx/bxstringctor", func_0026AD70);

//100%
INCLUDE_ASM("bx/bxstringctor", func_0026ADA0__FPv);
#ifdef SKIP_ASM
void func_0026ADA0(void* self)
{
}
#endif

INCLUDE_ASM("bx/bxstringctor", func_0026ADF0);

INCLUDE_ASM("bx/bxstringctor", func_0026AF00);

//100%
INCLUDE_ASM("bx/bxstringctor", func_0026AF70);
#ifdef SKIP_ASM
extern "C" int func_0026AF70(void* self, int a1)
{
    return *(int*)((char*)self + 0x14) + a1 * 0x3c;
}
#endif

//100%
INCLUDE_ASM("bx/bxstringctor", func_0026AF88);
#ifdef SKIP_ASM
extern "C" int func_0026AF88(void* self, int a1)
{
    return *(int*)((char*)self + 0xc) + (a1 << 6);
}
#endif

extern "C" void* func_0026AFB8(void*);

//91.43%
INCLUDE_ASM("bx/bxstringctor", func_0026AF98__FPv);
#ifdef SKIP_ASM
void* func_0026AF98(void* self)
{
    return func_0026AFB8(self);
}
#endif

INCLUDE_ASM("bx/bxstringctor", func_0026AFB8);

INCLUDE_ASM("bx/bxstringctor", func_0026B178);

