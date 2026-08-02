#include "common.h"

INCLUDE_ASM("fe/ovstatereplay", cOVState_REPLAY_onWidgetCreate);

INCLUDE_ASM("fe/ovstatereplay", func_0020DF10);

INCLUDE_ASM("fe/ovstatereplay", func_0020DF38);

INCLUDE_ASM("fe/ovstatereplay", cOVState_REPLAY_onUpdate);

INCLUDE_ASM("fe/ovstatereplay", cOVState_REPLAY_setupCameraName);

INCLUDE_ASM("fe/ovstatereplay", cOVState_REPLAY_setupTicker);

extern "C" void* func_0039E6B8(void* self);

//100%
INCLUDE_ASM("fe/ovstatereplay", func_0020E8E0__FPv);
#ifdef SKIP_ASM
void* func_0020E8E0(void* self)
{
    return func_0039E6B8(self);
}
#endif

INCLUDE_ASM("fe/ovstatereplay", func_0020E900);

