#include "common.h"

INCLUDE_ASM("world/worldcache", cWorldBlockAllocator_init);

INCLUDE_ASM("world/worldcache", func_003A76C0);

//51.2%
INCLUDE_ASM("world/worldcache", func_003A7768__FPv);
#ifdef SKIP_ASM
int func_003A7768(void* self)
{
    *(int*)((char*)self + 0x8) = (int)((char*)*(void**)((char*)self + 0x8) - 0x1);
    *(int*)((char*)self + 0x10) = *(int*)((char*)*(void**)((char*)self + 0x10) + 0x14);
    *(int*)((char*)*(void**)((char*)self + 0x10) + 0x10) = 1;
    return *(int*)((char*)self + 0x10);
}
#endif

//9.12%
INCLUDE_ASM("world/worldcache", func_003A7790__FPvT0);
#ifdef SKIP_ASM
void* func_003A7790(void* self, void* a1)
{
    void* t0 = (char*)*(void**)((char*)self + 0x8) + 0x1;
    *(int*)((char*)a1 + 0x10) = 0;
    *(int*)((char*)a1 + 0x14) = *(int*)((char*)self + 0x10);
    *(int*)((char*)self + 0x10) = (int)a1;
    *(int*)((char*)self + 0x8) = (int)t0;
    return t0;
}
#endif

//100%
INCLUDE_ASM("world/worldcache", func_003A77B0__FPvii);
#ifdef SKIP_ASM
void* func_003A77B0(void* self, int a1, int a2)
{
    int t0 = 0;
    *(int*)((char*)self + 0x4) = a2;
    *(int*)self = a1;
    *(int*)((char*)self + 0x8) = t0;
    *(int*)((char*)self + 0xc) = t0;
    *(int*)((char*)self + 0x10) = t0;
    return self;
}
#endif

INCLUDE_ASM("world/worldcache", func_003A77D0);

INCLUDE_ASM("world/worldcache", func_003A7818);

INCLUDE_ASM("world/worldcache", func_003A7878);

INCLUDE_ASM("world/worldcache", func_003A7A20);

INCLUDE_ASM("world/worldcache", func_003A7AA8);

INCLUDE_ASM("world/worldcache", cWorldMemoryMan_activateSectionMem);

INCLUDE_ASM("world/worldcache", func_003A7B98);

INCLUDE_ASM("world/worldcache", cHullPage_cHullPage);

INCLUDE_ASM("world/worldcache", func_003A7C30);

INCLUDE_ASM("world/worldcache", cWorldCacheTable_cWorldCacheTable);

INCLUDE_ASM("world/worldcache", func_003A7D80);

INCLUDE_ASM("world/worldcache", func_003A7DD0);

INCLUDE_ASM("world/worldcache", func_003A7E38);

INCLUDE_ASM("world/worldcache", func_003A7E98);

INCLUDE_ASM("world/worldcache", func_003A7F90);

INCLUDE_ASM("world/worldcache", cWorldCache_init);

INCLUDE_ASM("world/worldcache", cWorldCache_activateSectionMem);

INCLUDE_ASM("world/worldcache", func_003A8230);

INCLUDE_ASM("world/worldcache", func_003A8290);

INCLUDE_ASM("world/worldcache", func_003A82C8);

INCLUDE_ASM("world/worldcache", func_003A8330);

INCLUDE_ASM("world/worldcache", func_003A8448);

INCLUDE_ASM("world/worldcache", func_003A84C8);

INCLUDE_ASM("world/worldcache", func_003A84F8);

INCLUDE_ASM("world/worldcache", func_003A8528);

INCLUDE_ASM("world/worldcache", func_003A8618);

INCLUDE_ASM("world/worldcache", func_003A8638);

INCLUDE_ASM("world/worldcache", func_003A8650);

INCLUDE_ASM("world/worldcache", cWorldCache_updatePages);

INCLUDE_ASM("world/worldcache", func_003A88A8);

INCLUDE_ASM("world/worldcache", cWorldCache_addBxStreamDataTest);

INCLUDE_ASM("world/worldcache", func_003A8CD0);

INCLUDE_ASM("world/worldcache", func_003A8E20);

INCLUDE_ASM("world/worldcache", func_003A8F10);

INCLUDE_ASM("world/worldcache", func_003A8F80);

INCLUDE_ASM("world/worldcache", func_003A8FB8);

INCLUDE_ASM("world/worldcache", func_003A9000);

//100%
INCLUDE_ASM("world/worldcache", func_003A9180__FPv);
#ifdef SKIP_ASM
void func_003A9180(void* self)
{
}
#endif

INCLUDE_ASM("world/worldcache", func_003A9188);

INCLUDE_ASM("world/worldcache", func_003A9258);

INCLUDE_ASM("world/worldcache", func_003A9558);

INCLUDE_ASM("world/worldcache", func_003A95C0);

INCLUDE_ASM("world/worldcache", func_003A9658);

INCLUDE_ASM("world/worldcache", func_003A96E0);

INCLUDE_ASM("world/worldcache", func_003A9770);

