#include "common.h"

void operator_delete(int* ptr);

//100%
INCLUDE_ASM("camera/trigger/cameratriggervolumes", tCameraTrigger__tCameraTrigger__FPvi);
#ifdef SKIP_ASM
void tCameraTrigger__tCameraTrigger(void* self, int flags)
{
    if (flags & 1) {
        operator_delete((int*)self);
    }
}
#endif

INCLUDE_ASM("camera/trigger/cameratriggervolumes", func_0016C5D0);

INCLUDE_ASM("camera/trigger/cameratriggervolumes", func_0016C5E0);

