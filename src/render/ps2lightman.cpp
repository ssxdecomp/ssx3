#include "common.h"

extern void* D_004936D8[16];
extern void* D_004A5B8C;

struct cPSPLightMan {
    void* vtable;
};

//99.83%
INCLUDE_ASM("render/ps2lightman", cPSPLightMan_cPSPLightMan__FP12cPSPLightMan);
#ifdef SKIP_ASM
cPSPLightMan* cPSPLightMan_cPSPLightMan(cPSPLightMan* self)
{
    self->vtable = D_004936D8;
    D_004A5B8C = self;
    return self;
}
#endif

INCLUDE_ASM("render/ps2lightman", func_0038AE28);

