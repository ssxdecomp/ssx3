#include "common.h"

INCLUDE_ASM("camera/trigger/cameratriggerman", cCameraTriggerMan_cleanupOnExit);

//100%
INCLUDE_ASM("camera/trigger/cameratriggerman", func_0016CA10__FPv);
#ifdef SKIP_ASM
void func_0016CA10(void* self)
{
}
#endif

INCLUDE_ASM("camera/trigger/cameratriggerman", cCameraTriggerMan_purge);

INCLUDE_ASM("camera/trigger/cameratriggerman", cCameraTriggerMan_loadTriggers);

INCLUDE_ASM("camera/trigger/cameratriggerman", cCameraTriggerMan_streamIn);

INCLUDE_ASM("camera/trigger/cameratriggerman", func_0016CEC8);

INCLUDE_ASM("camera/trigger/cameratriggerman", func_0016CEF0);

INCLUDE_ASM("camera/trigger/cameratriggerman", func_0016CF18);

//100%
INCLUDE_ASM("camera/trigger/cameratriggerman", func_0016CF40__FPv);
#ifdef SKIP_ASM
void func_0016CF40(void* self)
{
}
#endif

INCLUDE_ASM("camera/trigger/cameratriggerman", func_0016CF48);

extern "C" void* func_0016CF48(void* self, int type);

//100%
INCLUDE_ASM("camera/trigger/cameratriggerman", cCameraTriggerMan_setInGameTriggers__FPv);
#ifdef SKIP_ASM
void cCameraTriggerMan_setInGameTriggers(void* self)
{
    func_0016CF48(self, 2);
}
#endif

//99.29%
INCLUDE_ASM("camera/trigger/cameratriggerman", func_0016D1D8__FPv);
#ifdef SKIP_ASM
void* func_0016D1D8(void* self)
{
    return func_0016CF48(self, 1);
}
#endif

struct cCameraTriggerStack {
    int field_0x0;
    int field_0x4;
};

//100%
INCLUDE_ASM("camera/trigger/cameratriggerman", cCameraTriggerStack_init__FP19cCameraTriggerStack);
#ifdef SKIP_ASM
void cCameraTriggerStack_init(cCameraTriggerStack* self)
{
    self->field_0x0 = 0;
    self->field_0x4 = 0;
}
#endif

INCLUDE_ASM("camera/trigger/cameratriggerman", func_0016D210);

INCLUDE_ASM("camera/trigger/cameratriggerman", func_0016D238);

INCLUDE_ASM("camera/trigger/cameratriggerman", func_0016D260);

INCLUDE_ASM("camera/trigger/cameratriggerman", func_0016D320);

INCLUDE_ASM("camera/trigger/cameratriggerman", func_0016E1D8);

INCLUDE_ASM("camera/trigger/cameratriggerman", func_0016E560);

INCLUDE_ASM("camera/trigger/cameratriggerman", func_0016F068);

INCLUDE_ASM("camera/trigger/cameratriggerman", func_0016FBB8);

INCLUDE_ASM("camera/trigger/cameratriggerman", func_00170240);

INCLUDE_ASM("camera/trigger/cameratriggerman", func_001707B0);

INCLUDE_ASM("camera/trigger/cameratriggerman", func_00170D20);

