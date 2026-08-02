#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void func_0014F418(void* self);
extern const char D_0045A6B0[];
extern void* D_0045ADC8[16];
extern void* D_004A120C;

struct cBEOptionInterface {
    char pad_0x00[8];
    int field_0x8;
    void* vtable;
};

//92.24% - post-call register/global-reload scheduling not fully reproduced
INCLUDE_ASM("be/beintoption", cBEOptionInterface_getThis__Fv);
#ifdef SKIP_ASM
void* cBEOptionInterface_getThis()
{
    if (D_004A120C == 0) {
        cBEOptionInterface* mem = (cBEOptionInterface*)cMemMan_alloc(0x10, D_0045A6B0, 0, 0);
        mem->vtable = D_0045ADC8;
        D_004A120C = mem;
        func_0014F418(mem);
        ((cBEOptionInterface*)D_004A120C)->field_0x8 = 0;
    }
    return D_004A120C;
}
#endif

INCLUDE_ASM("be/beintoption", func_0014F2A8);

INCLUDE_ASM("be/beintoption", func_0014F360);

INCLUDE_ASM("be/beintoption", func_0014F418);

INCLUDE_ASM("be/beintoption", func_0014F458);

INCLUDE_ASM("be/beintoption", func_0014F4F8);

INCLUDE_ASM("be/beintoption", func_0014F600);

INCLUDE_ASM("be/beintoption", func_0014F648);

int sprintf(char* buf, const char* fmt, ...);
int GetHashValue32(char* str);
extern const char D_0045A6C0[];

//100%
INCLUDE_ASM("be/beintoption", cBEOptionInterface_getDefaultQuickKeyMessageHashValue__FPvi);
#ifdef SKIP_ASM
int cBEOptionInterface_getDefaultQuickKeyMessageHashValue(void* self, int value)
{
    char buf[24];
    sprintf(buf, D_0045A6C0, value);
    return GetHashValue32(buf);
}
#endif

INCLUDE_ASM("be/beintoption", func_0014F6A8);

INCLUDE_ASM("be/beintoption", func_0014F6E8);

INCLUDE_ASM("be/beintoption", func_0014F758);

INCLUDE_ASM("be/beintoption", func_0014F7A8);

INCLUDE_ASM("be/beintoption", func_0014F7E8);

INCLUDE_ASM("be/beintoption", func_0014F810);

INCLUDE_ASM("be/beintoption", func_0014F870);

INCLUDE_ASM("be/beintoption", func_0014F898);

