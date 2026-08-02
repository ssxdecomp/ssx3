#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern const char D_0045A648[];
extern void* D_0045AD98[16];
extern void* D_004A1204;

struct cBENetworkInterface {
    char pad_0x00[8];
    int field_0x8;
    void* vtable;
};

//99.58%
INCLUDE_ASM("be/beintnetwork", cBENetworkInterface_getThis__Fv);
#ifdef SKIP_ASM
void* cBENetworkInterface_getThis()
{
    if (D_004A1204 == 0) {
        cBENetworkInterface* mem = (cBENetworkInterface*)cMemMan_alloc(0x10, D_0045A648, 0, 0);
        mem->field_0x8 = 0;
        mem->vtable = D_0045AD98;
        D_004A1204 = mem;
    }
    return D_004A1204;
}
#endif

INCLUDE_ASM("be/beintnetwork", func_0014E130);

INCLUDE_ASM("be/beintnetwork", func_0014E1F8);

INCLUDE_ASM("be/beintnetwork", func_0014E2C0);

INCLUDE_ASM("be/beintnetwork", func_0014E2C8);

INCLUDE_ASM("be/beintnetwork", func_0014E5C8);

INCLUDE_ASM("be/beintnetwork", func_0014E9C0);

INCLUDE_ASM("be/beintnetwork", func_0014E9F8);

INCLUDE_ASM("be/beintnetwork", func_0014EA90);

INCLUDE_ASM("be/beintnetwork", func_0014EB08);

INCLUDE_ASM("be/beintnetwork", func_0014EBB8);

INCLUDE_ASM("be/beintnetwork", func_0014EBD8);

INCLUDE_ASM("be/beintnetwork", func_0014EBF8);

INCLUDE_ASM("be/beintnetwork", func_0014ECA0);

INCLUDE_ASM("be/beintnetwork", func_0014EDD8);

INCLUDE_ASM("be/beintnetwork", func_0014EE28);

INCLUDE_ASM("be/beintnetwork", func_0014EE58);

INCLUDE_ASM("be/beintnetwork", func_0014EEC8);

