#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void cInstanceNode_getBoundBoxInfo(void* self, void* out);
extern const char D_0048E890[];

struct cFloatingNode {
    char pad_0x00[0x78];
    void* field_0x78;
};

//93.68%
INCLUDE_ASM("object/floatingnode", cFloatingNode_initInfo__FP13cFloatingNode);
#ifdef SKIP_ASM
void cFloatingNode_initInfo(cFloatingNode* self)
{
    void* mem = cMemMan_alloc(0x30, D_0048E890, 0x20000000, 0);
    self->field_0x78 = mem;
    cInstanceNode_getBoundBoxInfo(self, (char*)mem + 0x20);
}
#endif

INCLUDE_ASM("object/floatingnode", func_0034EF08);

INCLUDE_ASM("object/floatingnode", func_0034EF40);

INCLUDE_ASM("object/floatingnode", func_0034F048);

INCLUDE_ASM("object/floatingnode", func_0034F120);

INCLUDE_ASM("object/floatingnode", func_0034F600);

INCLUDE_ASM("object/floatingnode", func_0034F790);

INCLUDE_ASM("object/floatingnode", func_0034F930);

INCLUDE_ASM("object/floatingnode", func_0034FA88);

INCLUDE_ASM("object/floatingnode", func_0034FB00);

