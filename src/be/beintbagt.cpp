#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern const char D_0045A6D8[];

struct sVTableBAGT {
    char pad_0x00[0x10];
    short field_0x10;
    char pad_0x12[2];
    void (*fn)(void*);
};
extern sVTableBAGT D_0045ACD8;

struct cBEBAGTInterface {
    char pad_0x00[8];
    int field_0x8;
    void* vtable;
};
extern void* D_004A1210;

//83.17% - delay-slot scheduling of the vtable store vs. the vtable-fn call not reproduced
INCLUDE_ASM("be/beintbagt", cBEBAGTInterface_getThis__Fv);
#ifdef SKIP_ASM
void* cBEBAGTInterface_getThis()
{
    if (D_004A1210 == 0) {
        cBEBAGTInterface* mem = (cBEBAGTInterface*)cMemMan_alloc(0x10, D_0045A6D8, 0, 0);
        D_004A1210 = mem;
        mem->vtable = &D_0045ACD8;
        D_0045ACD8.fn((char*)mem + D_0045ACD8.field_0x10);
        ((cBEBAGTInterface*)D_004A1210)->field_0x8 = 0;
    }
    return D_004A1210;
}
#endif

INCLUDE_ASM("be/beintbagt", func_0014F960);

INCLUDE_ASM("be/beintbagt", func_0014FAD0);

INCLUDE_ASM("be/beintbagt", func_0014FC40);

INCLUDE_ASM("be/beintbagt", func_0014FD80);

INCLUDE_ASM("be/beintbagt", func_0014FE08);

INCLUDE_ASM("be/beintbagt", func_0014FEA8);

INCLUDE_ASM("be/beintbagt", func_0014FF90);

INCLUDE_ASM("be/beintbagt", func_0014FFB8);

INCLUDE_ASM("be/beintbagt", func_00150048);

struct sPad20 { char x; int pad[4]; };
extern sPad20 D_0045AEB8;

//100%
INCLUDE_ASM("be/beintbagt", func_001500D8);
#ifdef SKIP_ASM
extern "C" unsigned short func_001500D8(void* self, int a1, int a2)
{
    return *(unsigned short*)((char*)&D_0045AEB8 + a2 * 0x14);
}
#endif

//100%
INCLUDE_ASM("be/beintbagt", func_001500F8);
#ifdef SKIP_ASM
extern "C" unsigned short func_001500F8(void* self, int a1, int a2)
{
    char* p = (char*)&D_0045AEB8 + a2 * 0x14;
    return *(unsigned short*)(p + 0x2);
}
#endif

//100%
INCLUDE_ASM("be/beintbagt", func_00150118);
#ifdef SKIP_ASM
extern "C" unsigned short func_00150118(void* self, int a1, int a2)
{
    char* p = (char*)&D_0045AEB8 + a2 * 0x14;
    return *(unsigned short*)(p + 0x4);
}
#endif

//100%
INCLUDE_ASM("be/beintbagt", func_00150138);
#ifdef SKIP_ASM
extern "C" unsigned short func_00150138(void* self, int a1, int a2)
{
    char* p = (char*)&D_0045AEB8 + a2 * 0x14;
    return *(unsigned short*)(p + 0x6);
}
#endif

//100%
INCLUDE_ASM("be/beintbagt", func_00150158);
#ifdef SKIP_ASM
extern "C" unsigned short func_00150158(void* self, int a1, int a2)
{
    char* p = (char*)&D_0045AEB8 + a2 * 0x14;
    return *(unsigned short*)(p + 0x8);
}
#endif

//100%
INCLUDE_ASM("be/beintbagt", func_00150178);
#ifdef SKIP_ASM
extern "C" unsigned short func_00150178(void* self, int a1, int a2)
{
    char* p = (char*)&D_0045AEB8 + a2 * 0x14;
    return *(unsigned short*)(p + 0xa);
}
#endif

INCLUDE_ASM("be/beintbagt", func_00150198);

INCLUDE_ASM("be/beintbagt", func_001502C8);

INCLUDE_ASM("be/beintbagt", func_001503F8);

extern void* D_00530600[];

//100%
INCLUDE_ASM("be/beintbagt", func_00150528__FPvi);
#ifdef SKIP_ASM
int func_00150528(void* self, int a1)
{
    return *(int*)((char*)(void*)D_00530600 + a1 * 8);
}
#endif

//92.33%
INCLUDE_ASM("be/beintbagt", func_00150540__FPvi);
#ifdef SKIP_ASM
int func_00150540(void* self, int a1)
{
    return *(int*)((char*)((char*)(void*)D_00530600 + a1 * 8) + 0x4);
}
#endif

INCLUDE_ASM("be/beintbagt", func_00150558);

