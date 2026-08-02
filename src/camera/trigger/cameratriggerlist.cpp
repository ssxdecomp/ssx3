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

INCLUDE_ASM("camera/trigger/cameratriggerlist", cCameraTriggerList_insert);

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

