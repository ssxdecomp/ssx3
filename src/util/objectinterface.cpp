#include "common.h"

struct cObjectInterface {
    char pad_0x00[0x84];
    struct cObjectInterface_Impl* mImpl; // offset 0x84
};

struct cObjectInterface_Impl {
    char pad_0x00[0x88];
    void* mInstanceMan; // offset 0x88
};

extern cObjectInterface* D_004A28A8;

//100%
INCLUDE_ASM("util/objectinterface", cObjectInterface_getInstanceMan__Fv);
#ifdef SKIP_ASM
void* cObjectInterface_getInstanceMan()
{
    return D_004A28A8->mImpl->mInstanceMan;
}
#endif

extern "C" void* func_002D9C00(void* self);

//100%
INCLUDE_ASM("util/objectinterface", func_002D1CF0__FPv);
#ifdef SKIP_ASM
void* func_002D1CF0(void* self)
{
    return func_002D9C00(self);
}
#endif

INCLUDE_ASM("util/objectinterface", func_002D1D10);

INCLUDE_ASM("util/objectinterface", func_002D2058);

INCLUDE_ASM("util/objectinterface", func_002D2100);

//100%
INCLUDE_ASM("util/objectinterface", func_002D21B0__FPv);
#ifdef SKIP_ASM
void func_002D21B0(void* self)
{
}
#endif

//100%
INCLUDE_ASM("util/objectinterface", func_002D21B8__FPv);
#ifdef SKIP_ASM
void func_002D21B8(void* self)
{
}
#endif

INCLUDE_ASM("util/objectinterface", func_002D21C0);

