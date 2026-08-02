#include "common.h"

struct cRiderSphereTree {
    char pad_0x00[0x24];
    int field_0x24;
    int field_0x28;
};

//0% - target has extra dead constant load + redundant -1 materialization not yet reproduced
INCLUDE_ASM("intersect/riderspheretree", cRiderSphereTree_cRiderSphereTree__FP16cRiderSphereTree);
#ifdef SKIP_ASM
cRiderSphereTree* cRiderSphereTree_cRiderSphereTree(cRiderSphereTree* self)
{
    self->field_0x24 = -1;
    self->field_0x28 = -1;
    return self;
}
#endif

INCLUDE_ASM("intersect/riderspheretree", func_00329970);

INCLUDE_ASM("intersect/riderspheretree", func_003299C8);

INCLUDE_ASM("intersect/riderspheretree", func_00329A28);

INCLUDE_ASM("intersect/riderspheretree", func_00329A90);

INCLUDE_ASM("intersect/riderspheretree", func_00329AE0);

INCLUDE_ASM("intersect/riderspheretree", func_00329B40);

INCLUDE_ASM("intersect/riderspheretree", func_00329B90);

INCLUDE_ASM("intersect/riderspheretree", func_00329DC8);

INCLUDE_ASM("intersect/riderspheretree", func_00329F98);

INCLUDE_ASM("intersect/riderspheretree", func_0032A1C0);

INCLUDE_ASM("intersect/riderspheretree", func_0032AA28);

INCLUDE_ASM("intersect/riderspheretree", func_0032B2B8);

INCLUDE_ASM("intersect/riderspheretree", func_0032B620);

INCLUDE_ASM("intersect/riderspheretree", func_0032B6A8);

INCLUDE_ASM("intersect/riderspheretree", func_0032B6E0);

INCLUDE_ASM("intersect/riderspheretree", func_0032C0F8);

INCLUDE_ASM("intersect/riderspheretree", func_0032C508);

INCLUDE_ASM("intersect/riderspheretree", func_0032C540);

INCLUDE_ASM("intersect/riderspheretree", func_0032C590);

INCLUDE_ASM("intersect/riderspheretree", func_0032C5A8);

INCLUDE_ASM("intersect/riderspheretree", func_0032C630);

INCLUDE_ASM("intersect/riderspheretree", func_0032C648);

INCLUDE_ASM("intersect/riderspheretree", func_0032C770);

INCLUDE_ASM("intersect/riderspheretree", func_0032C898);

INCLUDE_ASM("intersect/riderspheretree", func_0032C928);

INCLUDE_ASM("intersect/riderspheretree", func_0032CA78);

INCLUDE_ASM("intersect/riderspheretree", func_0032CB58);

INCLUDE_ASM("intersect/riderspheretree", func_0032CBF8);

INCLUDE_ASM("intersect/riderspheretree", func_0032CDB0);

INCLUDE_ASM("intersect/riderspheretree", func_0032D028);

INCLUDE_ASM("intersect/riderspheretree", func_0032D440);

INCLUDE_ASM("intersect/riderspheretree", func_0032D470);

INCLUDE_ASM("intersect/riderspheretree", func_0032DA40);

INCLUDE_ASM("intersect/riderspheretree", func_0032DB40);

INCLUDE_ASM("intersect/riderspheretree", func_0032DC10);

INCLUDE_ASM("intersect/riderspheretree", func_0032DE20);

INCLUDE_ASM("intersect/riderspheretree", func_0032DF28);

INCLUDE_ASM("intersect/riderspheretree", func_0032E100);

INCLUDE_ASM("intersect/riderspheretree", func_0032E288);

INCLUDE_ASM("intersect/riderspheretree", func_0032E398);

INCLUDE_ASM("intersect/riderspheretree", func_0032E4B8);

INCLUDE_ASM("intersect/riderspheretree", func_0032E4D0);

INCLUDE_ASM("intersect/riderspheretree", func_0032E5E8);

//100%
INCLUDE_ASM("intersect/riderspheretree", func_0032E688__FPv);
#ifdef SKIP_ASM
int func_0032E688(void* self)
{
    return 0;
}
#endif

INCLUDE_ASM("intersect/riderspheretree", func_0032E690);

INCLUDE_ASM("intersect/riderspheretree", func_0032E9A0);

INCLUDE_ASM("intersect/riderspheretree", func_0032F650);

INCLUDE_ASM("intersect/riderspheretree", func_0032F708);

INCLUDE_ASM("intersect/riderspheretree", func_0032F760);

INCLUDE_ASM("intersect/riderspheretree", func_0032F840);

//100%
INCLUDE_ASM("intersect/riderspheretree", func_0032F8B0__FPv);
#ifdef SKIP_ASM
int func_0032F8B0(void* self)
{
    int t0 = *(int*)((char*)self + 0x64);
    *(int*)((char*)self + 0x4) = 0;
    *(int*)((char*)self + 0x60) = t0;
    return t0;
}
#endif

INCLUDE_ASM("intersect/riderspheretree", func_0032F8C0);

INCLUDE_ASM("intersect/riderspheretree", func_0032F8F0);

INCLUDE_ASM("intersect/riderspheretree", func_0032F990);

INCLUDE_ASM("intersect/riderspheretree", func_0032FA30);

INCLUDE_ASM("intersect/riderspheretree", func_0032FAC0);

INCLUDE_ASM("intersect/riderspheretree", func_0032FB48);

INCLUDE_ASM("intersect/riderspheretree", func_0032FC08);

INCLUDE_ASM("intersect/riderspheretree", func_0032FD40);

INCLUDE_ASM("intersect/riderspheretree", func_0032FD98);

INCLUDE_ASM("intersect/riderspheretree", func_0032FDB0);

INCLUDE_ASM("intersect/riderspheretree", func_0032FE40);

INCLUDE_ASM("intersect/riderspheretree", func_0032FE78);

INCLUDE_ASM("intersect/riderspheretree", func_0032FFA0);

INCLUDE_ASM("intersect/riderspheretree", func_003300F8);

INCLUDE_ASM("intersect/riderspheretree", func_00330128);

INCLUDE_ASM("intersect/riderspheretree", func_00330250);

INCLUDE_ASM("intersect/riderspheretree", func_00330360);

