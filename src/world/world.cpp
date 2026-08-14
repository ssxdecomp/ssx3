#include "common.h"

INCLUDE_ASM("world/world", cWorld_cWorld);

INCLUDE_ASM("world/world", func_003A6740);

extern "C" void cWorld_resetMap(void*);

//100%
INCLUDE_ASM("world/world", func_003A67E0);
#ifdef SKIP_ASM
extern "C" void func_003A67E0(void* self)
{
    cWorld_resetMap(self);
}
#endif

INCLUDE_ASM("world/world", cWorld_resetMap);

extern "C" void* func_003A8290(int);

//100%
INCLUDE_ASM("world/world", func_003A6928__FPv);
#ifdef SKIP_ASM
void* func_003A6928(void* self)
{
    return func_003A8290(*(int*)self);
}
#endif

INCLUDE_ASM("world/world", func_003A6948);

INCLUDE_ASM("world/world", func_003A6AE0);

INCLUDE_ASM("world/world", func_003A6B78);

INCLUDE_ASM("world/world", func_003A6BA8);

INCLUDE_ASM("world/world", func_003A6BD8);

INCLUDE_ASM("world/world", func_003A6C08);

INCLUDE_ASM("world/world", func_003A6C38);

INCLUDE_ASM("world/world", func_003A6C68);

INCLUDE_ASM("world/world", func_003A6C98);

//100%
INCLUDE_ASM("world/world", func_003A6CC8__FPvT0);
#ifdef SKIP_ASM
int func_003A6CC8(void* self, void* a1)
{
    return *(int*)((char*)*(void**)((char*)*(void**)((char*)a1 + 0x88) + 0xc) + 0x8);
}
#endif

//100%
INCLUDE_ASM("world/world", func_003A6CD8__FPvT0);
#ifdef SKIP_ASM
int func_003A6CD8(void* self, void* a1)
{
    return *(int*)((char*)*(void**)((char*)*(void**)((char*)a1 + 0x88) + 0xc) + 0x8);
}
#endif

//100%
INCLUDE_ASM("world/world", func_003A6CE8);
#ifdef SKIP_ASM
extern "C" void* func_003A6CE8(void* self, int a1)
{
    return (char*)(*(void**)self) + a1 * 0x140;
}
#endif

//100%
INCLUDE_ASM("world/world", func_003A6D00__FPvi);
#ifdef SKIP_ASM
int func_003A6D00(void* self, int a1)
{
    return *(int*)((char*)*(void**)self + a1 * 4);
}
#endif

INCLUDE_ASM("world/world", func_003A6D18);

