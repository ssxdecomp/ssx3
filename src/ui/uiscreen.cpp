#include "common.h"

extern "C" void cListNode_removeFromList(void* self);

struct sDeleteTarget {
    char pad_0x00[0x8];
    short field_0x8;
    char pad_0xA[2];
    void (*fn)(void*, int); // 0xC
};

//100%
INCLUDE_ASM("ui/uiscreen", cUIThread_deleteThread__FPv);
#ifdef SKIP_ASM
void cUIThread_deleteThread(void* self)
{
    cListNode_removeFromList(self);
    if (self != 0) {
        sDeleteTarget* target = *(sDeleteTarget**)((char*)self + 0x8);
        target->fn((char*)self + target->field_0x8, 3);
    }
}
#endif

INCLUDE_ASM("ui/uiscreen", func_0039C558);

INCLUDE_ASM("ui/uiscreen", cUIScreen_setData);

INCLUDE_ASM("ui/uiscreen", func_0039C728);

struct sFrameEntry {
    int label; // 0x0
    int stride; // 0x4
    unsigned short field_0x8; // 0x8
};

struct sFrameList {
    int count; // 0x0
};

struct cUIScreen {
    char pad_0x00[0x34];
    sFrameList* list; // 0x34
};

//44.71% - loop control-flow shape (bnel/lazy-stride idiom) not reproduced after several attempts; logic is correct
INCLUDE_ASM("ui/uiscreen", cUIScreen_getFrameByLabel__FP9cUIScreeni);
#ifdef SKIP_ASM
unsigned short cUIScreen_getFrameByLabel(cUIScreen* self, int label)
{
    sFrameList* list = self->list;
    int count = list->count;
    if (count == 0) {
        return 0xFFFF;
    }
    char* entry = (char*)list + 4;
    int idx = 0;
    do {
        sFrameEntry* e = (sFrameEntry*)entry;
        if (e->label == label) {
            return e->field_0x8;
        }
        int stride = e->stride;
        idx++;
        entry += stride;
    } while (idx < count);
    return 0xFFFF;
}
#endif

INCLUDE_ASM("ui/uiscreen", cUIScreen_getPrimaryThread);

INCLUDE_ASM("ui/uiscreen", cUIScreen_jumpToFrame);

INCLUDE_ASM("ui/uiscreen", cUIScreen_playFrame);

INCLUDE_ASM("ui/uiscreen", func_0039C978);

INCLUDE_ASM("ui/uiscreen", func_0039CBC8);

INCLUDE_ASM("ui/uiscreen", func_0039CBE0);

INCLUDE_ASM("ui/uiscreen", func_0039CC38);

INCLUDE_ASM("ui/uiscreen", func_0039CCA8);

INCLUDE_ASM("ui/uiscreen", func_0039CD30);

INCLUDE_ASM("ui/uiscreen", func_0039CD90);

INCLUDE_ASM("ui/uiscreen", func_0039CD98);

INCLUDE_ASM("ui/uiscreen", func_0039CDA0);

INCLUDE_ASM("ui/uiscreen", func_0039CE20);

INCLUDE_ASM("ui/uiscreen", func_0039CE48);

INCLUDE_ASM("ui/uiscreen", func_0039CE90);

INCLUDE_ASM("ui/uiscreen", func_0039CE98);

INCLUDE_ASM("ui/uiscreen", cUIScreen_createAllObjects);

INCLUDE_ASM("ui/uiscreen", cUIScreen_createObjectByStruct);

INCLUDE_ASM("ui/uiscreen", func_0039D758);

INCLUDE_ASM("ui/uiscreen", func_0039D778);

INCLUDE_ASM("ui/uiscreen", cUIScreen_getObjectByHashName);

INCLUDE_ASM("ui/uiscreen", func_0039D8C0);

INCLUDE_ASM("ui/uiscreen", func_0039D948);

INCLUDE_ASM("ui/uiscreen", func_0039D968);

INCLUDE_ASM("ui/uiscreen", func_0039DA20);

INCLUDE_ASM("ui/uiscreen", func_0039DE68);

INCLUDE_ASM("ui/uiscreen", func_0039DF28);

INCLUDE_ASM("ui/uiscreen", func_0039DFB0);

INCLUDE_ASM("ui/uiscreen", func_0039DFE8);

INCLUDE_ASM("ui/uiscreen", func_0039E130);

INCLUDE_ASM("ui/uiscreen", func_0039E288);

INCLUDE_ASM("ui/uiscreen", func_0039E2A0);

INCLUDE_ASM("ui/uiscreen", func_0039E318);

INCLUDE_ASM("ui/uiscreen", func_0039E390);

INCLUDE_ASM("ui/uiscreen", func_0039E4A0);

INCLUDE_ASM("ui/uiscreen", func_0039E4C0);

INCLUDE_ASM("ui/uiscreen", func_0039E508);

INCLUDE_ASM("ui/uiscreen", func_0039E510);

INCLUDE_ASM("ui/uiscreen", func_0039E688);

INCLUDE_ASM("ui/uiscreen", func_0039E6B8);

INCLUDE_ASM("ui/uiscreen", func_0039E758);

INCLUDE_ASM("ui/uiscreen", func_0039E868);

