#include "common.h"

INCLUDE_ASM("ui/uistatestack", cUIStateStack_pushExplicit);

INCLUDE_ASM("ui/uistatestack", func_0039F290);

INCLUDE_ASM("ui/uistatestack", cUIStateStack_pushSpecial);

INCLUDE_ASM("ui/uistatestack", func_0039F400);

INCLUDE_ASM("ui/uistatestack", func_0039F4C0);

INCLUDE_ASM("ui/uistatestack", func_0039F600);

INCLUDE_ASM("ui/uistatestack", func_0039F698);

INCLUDE_ASM("ui/uistatestack", func_0039F718);

INCLUDE_ASM("ui/uistatestack", func_0039F7B8);

INCLUDE_ASM("ui/uistatestack", func_0039F840);

INCLUDE_ASM("ui/uistatestack", func_0039F8C8);

INCLUDE_ASM("ui/uistatestack", func_0039F9D8);

INCLUDE_ASM("ui/uistatestack", cUIStateStack_getCurrentState);

struct cList;
void* cList_first(cList*);

//100%
INCLUDE_ASM("ui/uistatestack", func_0039FAE8);
#ifdef SKIP_ASM
extern "C" void* func_0039FAE8(void* self)
{
    return cList_first((cList*)self);
}
#endif

INCLUDE_ASM("ui/uistatestack", func_0039FB30);

INCLUDE_ASM("ui/uistatestack", func_0039FC48);

INCLUDE_ASM("ui/uistatestack", func_0039FCC8);

INCLUDE_ASM("ui/uistatestack", func_0039FD38);

INCLUDE_ASM("ui/uistatestack", func_0039FE00);

INCLUDE_ASM("ui/uistatestack", func_0039FEB8);

//100%
INCLUDE_ASM("ui/uistatestack", func_0039FF50__FPv);
#ifdef SKIP_ASM
int func_0039FF50(void* self)
{
    return *(int*)((char*)*(void**)((char*)*(void**)((char*)self + 0x5c) + 0xd0) + 0x10);
}
#endif

//100%
INCLUDE_ASM("ui/uistatestack", func_0039FF60);
#ifdef SKIP_ASM
extern "C" void* func_0039FF60(void* self, int a1)
{
    return *(int*)((char*)self + 0x38) == a1 ? self : 0;
}
#endif

