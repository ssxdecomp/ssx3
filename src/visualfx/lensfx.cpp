#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
void* func_002EC418(void* self);
extern const char D_004A3B48[];

//99.23%
INCLUDE_ASM("visualfx/lensfx", cLensFxMan_construct__Fv);
#ifdef SKIP_ASM
void* cLensFxMan_construct()
{
    void* mem = cMemMan_alloc(0x6820, D_004A3B48, 0, 0);
    return func_002EC418(mem);
}
#endif

INCLUDE_ASM("visualfx/lensfx", func_002EC418);

extern void* D_00487F00[];
extern "C" void* func_002E3060(void*);

//100%
INCLUDE_ASM("visualfx/lensfx", func_002EC450__FPv);
#ifdef SKIP_ASM
void* func_002EC450(void* self)
{
    *(int*)((char*)self + 0x649c) = (int)(void*)D_00487F00;
    return func_002E3060(self);
}
#endif

INCLUDE_ASM("visualfx/lensfx", func_002EC478);

//100%
INCLUDE_ASM("visualfx/lensfx", func_002EC9D0__FPv);
#ifdef SKIP_ASM
void* func_002EC9D0(void* self)
{
    *(int*)self = -1;
    return self;
}
#endif

INCLUDE_ASM("visualfx/lensfx", func_002EC9E0);

INCLUDE_ASM("visualfx/lensfx", func_002ECA68);

INCLUDE_ASM("visualfx/lensfx", func_002ECAF0);

INCLUDE_ASM("visualfx/lensfx", func_002ECB28);

INCLUDE_ASM("visualfx/lensfx", func_002ECBC0);

INCLUDE_ASM("visualfx/lensfx", func_002ECC28);

INCLUDE_ASM("visualfx/lensfx", func_002ECCB8);

INCLUDE_ASM("visualfx/lensfx", func_002ECF78);

INCLUDE_ASM("visualfx/lensfx", func_002ECFA0);

INCLUDE_ASM("visualfx/lensfx", func_002ED048);

INCLUDE_ASM("visualfx/lensfx", func_002ED1D0);

INCLUDE_ASM("visualfx/lensfx", func_002ED338);

INCLUDE_ASM("visualfx/lensfx", func_002ED490);

INCLUDE_ASM("visualfx/lensfx", func_002EDB20);

INCLUDE_ASM("visualfx/lensfx", func_002EDF00);

INCLUDE_ASM("visualfx/lensfx", func_002EDFB8);

INCLUDE_ASM("visualfx/lensfx", func_002EDFD0);

INCLUDE_ASM("visualfx/lensfx", func_002EE010);

INCLUDE_ASM("visualfx/lensfx", func_002EE070);

INCLUDE_ASM("visualfx/lensfx", func_002EE0B8);

INCLUDE_ASM("visualfx/lensfx", func_002EE100);

INCLUDE_ASM("visualfx/lensfx", func_002EE148);

INCLUDE_ASM("visualfx/lensfx", func_002EE190);

INCLUDE_ASM("visualfx/lensfx", func_002EE1D8);

INCLUDE_ASM("visualfx/lensfx", func_002EE220);

INCLUDE_ASM("visualfx/lensfx", func_002EE268);

INCLUDE_ASM("visualfx/lensfx", func_002EE2B0);

INCLUDE_ASM("visualfx/lensfx", func_002EE2F8);

INCLUDE_ASM("visualfx/lensfx", func_002EE318);

INCLUDE_ASM("visualfx/lensfx", func_002EE340);

INCLUDE_ASM("visualfx/lensfx", func_002EE368);

INCLUDE_ASM("visualfx/lensfx", func_002EE3B8);

INCLUDE_ASM("visualfx/lensfx", func_002EE400);

INCLUDE_ASM("visualfx/lensfx", func_002EE448);

INCLUDE_ASM("visualfx/lensfx", func_002EE4C0);

INCLUDE_ASM("visualfx/lensfx", func_002EE508);

INCLUDE_ASM("visualfx/lensfx", func_002EE570);

INCLUDE_ASM("visualfx/lensfx", func_002EE5B8);

INCLUDE_ASM("visualfx/lensfx", func_002EE600);

INCLUDE_ASM("visualfx/lensfx", func_002EE660);

INCLUDE_ASM("visualfx/lensfx", func_002EE6A8);

INCLUDE_ASM("visualfx/lensfx", func_002EE6F0);

INCLUDE_ASM("visualfx/lensfx", func_002EE738);

INCLUDE_ASM("visualfx/lensfx", func_002EE780);

