#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern const char D_0047C520[];
extern void* D_0047D0E8[16];

struct cStreamPause {
    void* vtable;
};

//99.67%
INCLUDE_ASM("main/streampause", cStreamPause_construct__Fv);
#ifdef SKIP_ASM
cStreamPause* cStreamPause_construct()
{
    cStreamPause* self = (cStreamPause*)cMemMan_alloc(4, D_0047C520, 0x20000000, 0);
    self->vtable = D_0047D0E8;
    return self;
}
#endif

INCLUDE_ASM("main/streampause", func_00242EB8);

INCLUDE_ASM("main/streampause", func_00243838);

