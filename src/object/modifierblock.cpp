#include "common.h"

struct sBoundBoxTarget {
    char pad_0x00[0x68];
    short field_0x68;
    char pad_0x6A[2];
    void (*fnBoundBox)(void*); // 0x6C
    char pad_0x70[0x78 - 0x70];
    short field_0x78;
    char pad_0x7A[2];
    void (*fnRadius)(void*); // 0x7C
};

struct sBoundBoxNode {
    sBoundBoxTarget* target; // 0x0
};

struct tModifierBlock {
    sBoundBoxNode* node; // 0x0
    int field_0x4;
    int field_0x8;
    int field_0xC;
    int field_0x10;
    int field_0x14;
    void* field_0x18;
    int field_0x1C;
    int field_0x20;
    void* field_0x24;
};

extern void* D_00491340[16];
extern void* D_00491200[16];

//100%
INCLUDE_ASM("object/modifierblock", tModifierBlock_tModifierBlock__FP14tModifierBlock);
#ifdef SKIP_ASM
tModifierBlock* tModifierBlock_tModifierBlock(tModifierBlock* self)
{
    self->field_0x18 = D_00491340;
    self->field_0x24 = D_00491200;
    self->field_0x10 = 0;
    self->field_0x14 = 0;
    self->field_0x1C = 0;
    self->field_0x20 = 0;
    self->node = 0;
    self->field_0x4 = 0;
    self->field_0x8 = 0;
    self->field_0xC = 0;
    return self;
}
#endif

INCLUDE_ASM("object/modifierblock", func_00352AE8);

INCLUDE_ASM("object/modifierblock", func_00352B88);

//98.46% - target uses a2 for `node`, unclear source shape reproduces that register choice
INCLUDE_ASM("object/modifierblock", tModifierBlock_setBoundBox__FP14tModifierBlock);
#ifdef SKIP_ASM
void tModifierBlock_setBoundBox(tModifierBlock* self)
{
    sBoundBoxNode* node = self->node;
    if (node != 0) {
        sBoundBoxTarget* target = node->target;
        target->fnBoundBox((char*)node + target->field_0x68);
    }
}
#endif

INCLUDE_ASM("object/modifierblock", func_00352BF8);

//100%
INCLUDE_ASM("object/modifierblock", tModifierBlock_setRadius__FP14tModifierBlock);
#ifdef SKIP_ASM
void tModifierBlock_setRadius(tModifierBlock* self)
{
    sBoundBoxNode* node = self->node;
    if (node != 0) {
        sBoundBoxTarget* target = node->target;
        target->fnRadius((char*)node + target->field_0x78);
    }
}
#endif

INCLUDE_ASM("object/modifierblock", func_00352C70);

INCLUDE_ASM("object/modifierblock", func_00352D20);

INCLUDE_ASM("object/modifierblock", func_00352DD0);

INCLUDE_ASM("object/modifierblock", func_00352E50);

INCLUDE_ASM("object/modifierblock", func_00352ED0);

INCLUDE_ASM("object/modifierblock", func_00352F08);

INCLUDE_ASM("object/modifierblock", func_00352F40);

INCLUDE_ASM("object/modifierblock", func_00353020);

INCLUDE_ASM("object/modifierblock", func_00353098);

INCLUDE_ASM("object/modifierblock", func_003530D0);

INCLUDE_ASM("object/modifierblock", func_00353118);

INCLUDE_ASM("object/modifierblock", func_00353150);

INCLUDE_ASM("object/modifierblock", func_00353188);

INCLUDE_ASM("object/modifierblock", func_003531D0);

INCLUDE_ASM("object/modifierblock", func_00353228);

INCLUDE_ASM("object/modifierblock", func_00353278);

INCLUDE_ASM("object/modifierblock", func_00353300);

INCLUDE_ASM("object/modifierblock", func_00353398);

INCLUDE_ASM("object/modifierblock", func_00353418);

INCLUDE_ASM("object/modifierblock", func_00353448);

INCLUDE_ASM("object/modifierblock", tModifierBlock_readFromReplayFrame);

extern void* D_0048F008[];

//58.1%
INCLUDE_ASM("object/modifierblock", func_00353AC0__FPv);
#ifdef SKIP_ASM
void* func_00353AC0(void* self)
{
    int t0 = 0;
    *(int*)((char*)self + 0x10) = -1;
    *(int*)((char*)self + 0xc) = (int)(void*)D_0048F008;
    *(int*)((char*)self + 0x4) = t0;
    *(int*)((char*)self + 0x8) = t0;
    *(int*)((char*)self + 0x14) = t0;
    return self;
}
#endif

extern "C" void* func_003546C8(void*);

//100%
INCLUDE_ASM("object/modifierblock", func_00353AE8__FPv);
#ifdef SKIP_ASM
void* func_00353AE8(void* self)
{
    *(int*)((char*)self + 0xc) = (int)(void*)D_0048F008;
    return func_003546C8(self);
}
#endif

INCLUDE_ASM("object/modifierblock", func_00353B10);

INCLUDE_ASM("object/modifierblock", func_00353CF0);

//100%
INCLUDE_ASM("object/modifierblock", func_00353D98__FPv);
#ifdef SKIP_ASM
int func_00353D98(void* self)
{
    int t0 = -1;
    *(int*)((char*)self + 0x14) = 0;
    *(int*)((char*)self + 0x10) = t0;
    return t0;
}
#endif

//100%
INCLUDE_ASM("object/modifierblock", func_00353DA8__FPv);
#ifdef SKIP_ASM
void* func_00353DA8(void* self)
{
    *(int*)((char*)self + 0x24) = 0;
    return self;
}
#endif

INCLUDE_ASM("object/modifierblock", func_00353DB8);

INCLUDE_ASM("object/modifierblock", func_00353E08);

INCLUDE_ASM("object/modifierblock", func_00353E80);

