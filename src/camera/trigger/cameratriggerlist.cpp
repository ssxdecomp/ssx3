#include "common.h"

struct cCameraTriggerList {
    int field_0x0;
    int field_0x4;
    int field_0x8;
    int field_0xC;
    int field_0x10;
};

void cCameraTriggerList_initHeader(cCameraTriggerList* self);

//100%
INCLUDE_ASM("camera/trigger/cameratriggerlist", cCameraTriggerList_init__FP18cCameraTriggerList);
#ifdef SKIP_ASM
void cCameraTriggerList_init(cCameraTriggerList* self)
{
    self->field_0x0 = 0;
    cCameraTriggerList_initHeader(self);
}
#endif

INCLUDE_ASM("camera/trigger/cameratriggerlist", func_0016BF40);

INCLUDE_ASM("camera/trigger/cameratriggerlist", func_0016C098);

struct cCameraTriggerList2 {
    void** arr; // 0x0
    int count; // 0x4
};

//27.25% - target uses branch-likely (bgezl/bnel) for both conditions, ours compiles to regular branches; logic is correct, several restructuring attempts made it worse
INCLUDE_ASM("camera/trigger/cameratriggerlist", cCameraTriggerList_insert__FP19cCameraTriggerList2Pvi);
#ifdef SKIP_ASM
int cCameraTriggerList_insert(cCameraTriggerList2* list, void* item, int idx)
{
    if (idx >= 0) {
        list->arr[idx] = item;
        return 1;
    }
    int count = list->count;
    if (count < 0x78) {
        list->arr[count] = item;
        list->count = count + 1;
        return 1;
    }
    return 0;
}
#endif

INCLUDE_ASM("camera/trigger/cameratriggerlist", cCameraTriggerList_loadFromFile);

INCLUDE_ASM("camera/trigger/cameratriggerlist", cCameraTriggerList_loadFromBuffer);

//100%
INCLUDE_ASM("camera/trigger/cameratriggerlist", cCameraTriggerList_initHeader__FP18cCameraTriggerList);
#ifdef SKIP_ASM
void cCameraTriggerList_initHeader(cCameraTriggerList* self)
{
    self->field_0x4 = 0;
    self->field_0xC = 7;
    self->field_0x8 = 0;
    self->field_0x10 = 0;
}
#endif

void get_uint(void* buffer, void* dest);

//100%
INCLUDE_ASM("camera/trigger/cameratriggerlist", cCameraTriggerList_readCookie__FP18cCameraTriggerListPv);
#ifdef SKIP_ASM
void cCameraTriggerList_readCookie(cCameraTriggerList* self, void* buffer)
{
    get_uint(buffer, (char*)self + 0xC);
}
#endif

INCLUDE_ASM("camera/trigger/cameratriggerlist", cCameraTriggerList_readHeader);

