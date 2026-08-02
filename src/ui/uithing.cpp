#include "common.h"

struct cUIThing {
    char pad_0x00[0x3C];
    unsigned short* mEvents; // 0x3C
};

//100%
INCLUDE_ASM("ui/uithing", cUIThing_getKeyframerEvent__FP8cUIThingi);
#ifdef SKIP_ASM
unsigned short cUIThing_getKeyframerEvent(cUIThing* self, int x)
{
    signed char idx = (signed char)x;
    if (self->mEvents != 0) {
        return self->mEvents[idx];
    }
    return 0xFFFF;
}
#endif

INCLUDE_ASM("ui/uithing", func_0039FFA0);

INCLUDE_ASM("ui/uithing", func_003A0000);

INCLUDE_ASM("ui/uithing", func_003A0048);

INCLUDE_ASM("ui/uithing", func_003A0158);

INCLUDE_ASM("ui/uithing", func_003A0290);

INCLUDE_ASM("ui/uithing", func_003A0318);

INCLUDE_ASM("ui/uithing", func_003A0330);

INCLUDE_ASM("ui/uithing", func_003A0348);

INCLUDE_ASM("ui/uithing", func_003A03F0);

INCLUDE_ASM("ui/uithing", func_003A04F0);

INCLUDE_ASM("ui/uithing", func_003A0528);

