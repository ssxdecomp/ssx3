#include "common.h"

INCLUDE_ASM("be/be", cBE_getBE);

struct sBEInterfaceVTable {
    char pad_0x00[0x8];
    short field_0x8;
    char pad_0xA[2];
    void* (*fn)(void*);
};

struct sBEInterface {
    char pad_0x00[0x4];
    sBEInterfaceVTable* vtable;
};

extern sBEInterface* D_005308A8[];
extern int D_004A11F4;

//95.88%
INCLUDE_ASM("be/be", cBE_getInterface__Fv);
#ifdef SKIP_ASM
void* cBE_getInterface()
{
    sBEInterface* iface = D_005308A8[D_004A11F4];
    return iface->vtable->fn((char*)iface + iface->vtable->field_0x8);
}
#endif

INCLUDE_ASM("be/be", func_0014DD98);

INCLUDE_ASM("be/be", func_0014DE28);

INCLUDE_ASM("be/be", cBE_setState);

INCLUDE_ASM("be/be", func_0014DF08);

INCLUDE_ASM("be/be", cBE_readFromReplayFrame);

//100%
INCLUDE_ASM("be/be", func_0014E048);
#ifdef SKIP_ASM
extern "C" int func_0014E048()
{
    return 0xBB78;
}
#endif

INCLUDE_ASM("be/be", func_0014E050);

extern "C" void* func_0014A5E0(int);

//100%
INCLUDE_ASM("be/be", func_0014E0C0__FPvi);
#ifdef SKIP_ASM
void* func_0014E0C0(void* self, int a1)
{
    return func_0014A5E0(a1);
}
#endif

