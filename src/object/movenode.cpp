#include "common.h"

INCLUDE_ASM("object/movenode", cMoveNode_cMoveNode);

INCLUDE_ASM("object/movenode", func_003553C0);

INCLUDE_ASM("object/movenode", func_00355420);

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
struct tModifierBlock;
tModifierBlock* tModifierBlock_tModifierBlock(tModifierBlock* self);
extern const char D_0048E9D8[];

struct cMoveNode {
    char pad_0x00[0x1C];
    void* field_0x1C;
};

//100%
INCLUDE_ASM("object/movenode", cMoveNode_addModifierBlock__FP9cMoveNode);
#ifdef SKIP_ASM
void cMoveNode_addModifierBlock(cMoveNode* self)
{
    void* mem = cMemMan_alloc(0x28, D_0048E9D8, 0x20000000, 0);
    self->field_0x1C = tModifierBlock_tModifierBlock((tModifierBlock*)mem);
}
#endif

INCLUDE_ASM("object/movenode", func_003554B0);

INCLUDE_ASM("object/movenode", func_00355550);

INCLUDE_ASM("object/movenode", func_003555A8);

INCLUDE_ASM("object/movenode", func_00355600);

void cEffectLink_add(void* link, void* other);

//99.74%
INCLUDE_ASM("object/movenode", cMoveNode_addEffectModifier__FP9cMoveNodePv);
#ifdef SKIP_ASM
void cMoveNode_addEffectModifier(cMoveNode* self, void* effect)
{
    if (self->field_0x1C == 0) {
        cMoveNode_addModifierBlock(self);
    }
    cEffectLink_add((char*)self->field_0x1C + 0x10, effect);
}
#endif

INCLUDE_ASM("object/movenode", func_003556A8);

INCLUDE_ASM("object/movenode", func_003556F8);

INCLUDE_ASM("object/movenode", func_00355748);

INCLUDE_ASM("object/movenode", func_00355770);

INCLUDE_ASM("object/movenode", func_00355858);

INCLUDE_ASM("object/movenode", func_00355878);

INCLUDE_ASM("object/movenode", func_00355888);

INCLUDE_ASM("object/movenode", func_003558B8);

INCLUDE_ASM("object/movenode", func_00355918);

INCLUDE_ASM("object/movenode", func_00355978);

INCLUDE_ASM("object/movenode", func_003559F8);

INCLUDE_ASM("object/movenode", func_00355A78);

INCLUDE_ASM("object/movenode", func_00355AD0);

INCLUDE_ASM("object/movenode", cMoveNode_addSpline);

INCLUDE_ASM("object/movenode", func_00355B90);

INCLUDE_ASM("object/movenode", func_00355BF0);

INCLUDE_ASM("object/movenode", func_00355C50);

INCLUDE_ASM("object/movenode", cMoveNode_addParticle);

INCLUDE_ASM("object/movenode", cMoveNode_addDynamicParticle);

INCLUDE_ASM("object/movenode", func_00355DB8);

INCLUDE_ASM("object/movenode", func_00355E38);

INCLUDE_ASM("object/movenode", cMoveNode_addHalo);

INCLUDE_ASM("object/movenode", func_00355F10);

INCLUDE_ASM("object/movenode", func_00356020);

INCLUDE_ASM("object/movenode", func_00356078);

INCLUDE_ASM("object/movenode", func_003560C0);

INCLUDE_ASM("object/movenode", func_00356128);

INCLUDE_ASM("object/movenode", func_00356198);

INCLUDE_ASM("object/movenode", func_00356298);

INCLUDE_ASM("object/movenode", func_00356608);

INCLUDE_ASM("object/movenode", cMoveNode_setupOverlapSystem);

INCLUDE_ASM("object/movenode", func_003567E0);

INCLUDE_ASM("object/movenode", func_003568B0);

INCLUDE_ASM("object/movenode", func_003569D0);

INCLUDE_ASM("object/movenode", func_00356A00);

INCLUDE_ASM("object/movenode", func_00356A28);

INCLUDE_ASM("object/movenode", func_00356A70);

INCLUDE_ASM("object/movenode", func_00356AB8);

INCLUDE_ASM("object/movenode", func_00356AE0);

INCLUDE_ASM("object/movenode", func_00356B08);

INCLUDE_ASM("object/movenode", func_00356B30);

INCLUDE_ASM("object/movenode", func_00356BF0);

INCLUDE_ASM("object/movenode", func_00356C48);

INCLUDE_ASM("object/movenode", func_00356CC8);

INCLUDE_ASM("object/movenode", func_00356D48);

INCLUDE_ASM("object/movenode", func_00356DB0);

INCLUDE_ASM("object/movenode", func_00356E60);

INCLUDE_ASM("object/movenode", func_00356E98);

INCLUDE_ASM("object/movenode", func_00356EB8);

INCLUDE_ASM("object/movenode", func_00356F10);

INCLUDE_ASM("object/movenode", func_00356F68);

INCLUDE_ASM("object/movenode", func_00356FF0);

INCLUDE_ASM("object/movenode", func_00357000);

INCLUDE_ASM("object/movenode", func_00357038);

INCLUDE_ASM("object/movenode", func_00357090);

INCLUDE_ASM("object/movenode", func_00357108);

INCLUDE_ASM("object/movenode", func_00357210);

INCLUDE_ASM("object/movenode", func_00357278);

INCLUDE_ASM("object/movenode", func_003572E0);

INCLUDE_ASM("object/movenode", func_00357358);

INCLUDE_ASM("object/movenode", func_003573F8);

INCLUDE_ASM("object/movenode", func_00357528);

INCLUDE_ASM("object/movenode", func_00357538);

INCLUDE_ASM("object/movenode", func_00357660);

INCLUDE_ASM("object/movenode", func_003576D0);

INCLUDE_ASM("object/movenode", func_00357750);

INCLUDE_ASM("object/movenode", func_00357798);

INCLUDE_ASM("object/movenode", func_00357820);

INCLUDE_ASM("object/movenode", func_00357848);

INCLUDE_ASM("object/movenode", func_003578A8);

INCLUDE_ASM("object/movenode", func_00357918);

INCLUDE_ASM("object/movenode", func_00357950);

INCLUDE_ASM("object/movenode", func_003579A8);

INCLUDE_ASM("object/movenode", func_003579C8);

INCLUDE_ASM("object/movenode", func_00357A00);

INCLUDE_ASM("object/movenode", func_00357A78);

INCLUDE_ASM("object/movenode", func_00357AE8);

INCLUDE_ASM("object/movenode", func_00357B10);

INCLUDE_ASM("object/movenode", func_00357B38);

INCLUDE_ASM("object/movenode", func_00357B90);

INCLUDE_ASM("object/movenode", func_00357BF8);

INCLUDE_ASM("object/movenode", func_00357C50);

INCLUDE_ASM("object/movenode", func_00357CA8);

INCLUDE_ASM("object/movenode", func_00357D28);

INCLUDE_ASM("object/movenode", func_00357DD8);

INCLUDE_ASM("object/movenode", func_00357E80);

INCLUDE_ASM("object/movenode", func_00357FA0);

