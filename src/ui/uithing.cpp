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

//100%
INCLUDE_ASM("ui/uithing", func_003A0318);
#ifdef SKIP_ASM
extern "C" int func_003A0318(void* self, int a1)
{
    self = (char*)self + ((signed char)a1 << 2);
    return *(int*)((char*)self + 0x6c);
}
#endif

//100%
INCLUDE_ASM("ui/uithing", func_003A0330);
#ifdef SKIP_ASM
extern "C" void func_003A0330(void* self, int a1, int a2)
{
    self = (char*)self + ((signed char)a1 << 2);
    *(int*)((char*)self + 0x6c) = a2;
}
#endif

INCLUDE_ASM("ui/uithing", func_003A0348);

INCLUDE_ASM("ui/uithing", func_003A03F0);

INCLUDE_ASM("ui/uithing", func_003A04F0);

INCLUDE_ASM("ui/uithing", func_003A0528);

