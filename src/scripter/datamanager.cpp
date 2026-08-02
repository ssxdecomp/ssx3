#include "common.h"

INCLUDE_ASM("scripter/datamanager", cDataManager_cDataManager);

INCLUDE_ASM("scripter/datamanager", func_002758C0);

INCLUDE_ASM("scripter/datamanager", func_00275920);

INCLUDE_ASM("scripter/datamanager", func_00275A20);

INCLUDE_ASM("scripter/datamanager", func_00275B08);

INCLUDE_ASM("scripter/datamanager", func_00275B98);

//0.0%
INCLUDE_ASM("scripter/datamanager", func_00275CD0__FPvT0);
#ifdef SKIP_ASM
int func_00275CD0(void* self, void* a1)
{
    int t0 = 0;
    int t1 = *(int*)((char*)self + 0x8);
    *(int*)((char*)a1 + 0x8) = t0;
    *(int*)((char*)a1 + 0xc) = t0;
    *(int*)((char*)a1 + 0x10) = t0;
    *(int*)a1 = t0;
    *(int*)((char*)a1 + 0x4) = t0;
    *(int*)((char*)a1 + 0x14) = t1;
    *(int*)((char*)self + 0x8) = (int)a1;
    return t1;
}
#endif

//53.33%
INCLUDE_ASM("scripter/datamanager", func_00275CF8__FPv);
#ifdef SKIP_ASM
int func_00275CF8(void* self)
{
    *(int*)((char*)self + 0x8) = *(int*)((char*)*(void**)((char*)self + 0x8) + 0x14);
    *(int*)((char*)*(void**)((char*)self + 0x8) + 0x14) = 0;
    return *(int*)((char*)self + 0x8);
}
#endif

INCLUDE_ASM("scripter/datamanager", func_00275D10);

INCLUDE_ASM("scripter/datamanager", func_00275D90);

INCLUDE_ASM("scripter/datamanager", func_00275DD8);

INCLUDE_ASM("scripter/datamanager", func_00275ED0);

INCLUDE_ASM("scripter/datamanager", func_00276048);

INCLUDE_ASM("scripter/datamanager", func_00276270);

INCLUDE_ASM("scripter/datamanager", func_00276388);

INCLUDE_ASM("scripter/datamanager", func_002766B0);

INCLUDE_ASM("scripter/datamanager", func_002766D0);

INCLUDE_ASM("scripter/datamanager", func_00276868);

INCLUDE_ASM("scripter/datamanager", func_00276998);

INCLUDE_ASM("scripter/datamanager", func_00276B98);

INCLUDE_ASM("scripter/datamanager", func_00276BD8);

INCLUDE_ASM("scripter/datamanager", func_00276CA8);

INCLUDE_ASM("scripter/datamanager", func_00276CC8);

INCLUDE_ASM("scripter/datamanager", func_00276F48);

INCLUDE_ASM("scripter/datamanager", func_00277060);

INCLUDE_ASM("scripter/datamanager", func_002770C0);

INCLUDE_ASM("scripter/datamanager", func_002771C8);

INCLUDE_ASM("scripter/datamanager", func_00277298);

//100%
INCLUDE_ASM("scripter/datamanager", func_002772B8__FPv);
#ifdef SKIP_ASM
int func_002772B8(void* self)
{
    return *(int*)((char*)self + 0xB0);
}
#endif

INCLUDE_ASM("scripter/datamanager", func_002772C0);

INCLUDE_ASM("scripter/datamanager", func_00277310);

INCLUDE_ASM("scripter/datamanager", func_002773A0);

INCLUDE_ASM("scripter/datamanager", func_00277400);

INCLUDE_ASM("scripter/datamanager", func_00277450);

INCLUDE_ASM("scripter/datamanager", func_00277598);

INCLUDE_ASM("scripter/datamanager", func_002776E0);

INCLUDE_ASM("scripter/datamanager", func_00277778);

INCLUDE_ASM("scripter/datamanager", func_00277800);

INCLUDE_ASM("scripter/datamanager", func_00277838);

INCLUDE_ASM("scripter/datamanager", func_00277980);

INCLUDE_ASM("scripter/datamanager", func_00277C08);

INCLUDE_ASM("scripter/datamanager", func_00277DD8);

INCLUDE_ASM("scripter/datamanager", func_00277DE8);

//99.5%
INCLUDE_ASM("scripter/datamanager", func_00277F08__FPv);
#ifdef SKIP_ASM
int func_00277F08(void* self)
{
    int t0 = 0;
    int t1 = -1;
    *(int*)((char*)self + 0xc) = t0;
    *(int*)((char*)self + 0x4) = t1;
    *(int*)self = t0;
    *(int*)((char*)self + 0x8) = t0;
    return t1;
}
#endif

INCLUDE_ASM("scripter/datamanager", func_00277F20);

INCLUDE_ASM("scripter/datamanager", func_002780B8);

INCLUDE_ASM("scripter/datamanager", func_00278210);

INCLUDE_ASM("scripter/datamanager", func_00278308);

