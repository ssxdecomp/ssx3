#include "common.h"

INCLUDE_ASM("main/ssxapp", cSSXApp_cSSXApp);

INCLUDE_ASM("main/ssxapp", cSSXApp_init);

INCLUDE_ASM("main/ssxapp", cSSXApp_loadInputMap);

INCLUDE_ASM("main/ssxapp", cSSXApp_parseCommandLine);

extern "C" int func_00326C60(void* mgr);
extern void* D_004A28A0;

//99.9%
INCLUDE_ASM("main/ssxapp", cSSXApp_flush__Fv);
#ifdef SKIP_ASM
int cSSXApp_flush()
{
    if (D_004A28A0 != 0) {
        return func_00326C60(D_004A28A0);
    }
    return 0;
}
#endif

INCLUDE_ASM("main/ssxapp", cSSXApp_preUpdate);

extern "C" void func_00326B88(void* mgr);

//99.89%
INCLUDE_ASM("main/ssxapp", cSSXApp_timerCallback__Fv);
#ifdef SKIP_ASM
void cSSXApp_timerCallback()
{
    if (D_004A28A0 != 0) {
        func_00326B88(D_004A28A0);
    }
}
#endif

void* cMCOverlayManager_getManager();

//100%
INCLUDE_ASM("main/ssxapp", func_00227F80);
#ifdef SKIP_ASM
extern "C" void* func_00227F80()
{
    return cMCOverlayManager_getManager();
}
#endif

INCLUDE_ASM("main/ssxapp", cSSXApp_purge);

INCLUDE_ASM("main/ssxapp", cSSXApp_startGameLoad);

INCLUDE_ASM("main/ssxapp", func_00228238);

INCLUDE_ASM("main/ssxapp", cSSXApp_initload);

INCLUDE_ASM("main/ssxapp", cSSXApp_initLocale);

extern "C" void func_002B4B48(void* self);
extern "C" void func_00284C28();
extern "C" void cAppMan_loadexecpurge(void* self);

struct sExecPurgeVTable {
    char pad_0x00[0x3B8];
    short field_0x3B8;
    char pad_0x3BA[2];
    void (*fn)(void*);
};

struct sExecPurgeMgr {
    char pad_0x00[0x10D8];
    sExecPurgeVTable* vtable;
};

extern sExecPurgeMgr* D_004A5B80;

//99.95%
INCLUDE_ASM("main/ssxapp", cSSXApp_loadexecpurge__FPv);
#ifdef SKIP_ASM
void cSSXApp_loadexecpurge(void* self)
{
    func_002B4B48(self);
    func_00284C28();
    cAppMan_loadexecpurge(self);
    sExecPurgeVTable* vt = D_004A5B80->vtable;
    vt->fn((char*)D_004A5B80 + vt->field_0x3B8);
}
#endif

INCLUDE_ASM("main/ssxapp", func_00228C08);

INCLUDE_ASM("main/ssxapp", initOnline);

INCLUDE_ASM("main/ssxapp", func_00229180);

INCLUDE_ASM("main/ssxapp", func_00229278);

INCLUDE_ASM("main/ssxapp", func_002292E0);

INCLUDE_ASM("main/ssxapp", func_00229398);

INCLUDE_ASM("main/ssxapp", func_00229408);

INCLUDE_ASM("main/ssxapp", func_00229498);

INCLUDE_ASM("main/ssxapp", func_002294C8);

INCLUDE_ASM("main/ssxapp", func_00229530);

INCLUDE_ASM("main/ssxapp", func_00229738);

INCLUDE_ASM("main/ssxapp", func_00229788);

INCLUDE_ASM("main/ssxapp", func_002297D8);

INCLUDE_ASM("main/ssxapp", func_00229820);

INCLUDE_ASM("main/ssxapp", func_00229910);

//100%
INCLUDE_ASM("main/ssxapp", func_00229B90);
#ifdef SKIP_ASM
extern "C" void func_00229B90(void* self, int a1)
{
    ((unsigned int*)self)[a1 + 2] = 0xFFFFFFFFU;
}
#endif

INCLUDE_ASM("main/ssxapp", func_00229BA8);

INCLUDE_ASM("main/ssxapp", func_00229E20);

INCLUDE_ASM("main/ssxapp", func_00229E58);

INCLUDE_ASM("main/ssxapp", func_00229F30);

//100%
INCLUDE_ASM("main/ssxapp", func_00229F80__FPv);
#ifdef SKIP_ASM
void func_00229F80(void* self)
{
}
#endif

INCLUDE_ASM("main/ssxapp", func_00229F88);

INCLUDE_ASM("main/ssxapp", func_00229FC8);

INCLUDE_ASM("main/ssxapp", func_0022A128);

INCLUDE_ASM("main/ssxapp", func_0022A270);

INCLUDE_ASM("main/ssxapp", func_0022A368);

INCLUDE_ASM("main/ssxapp", func_0022A408);

INCLUDE_ASM("main/ssxapp", func_0022A4A8);

INCLUDE_ASM("main/ssxapp", func_0022A5A0);

INCLUDE_ASM("main/ssxapp", func_0022A698);

INCLUDE_ASM("main/ssxapp", func_0022A770);

INCLUDE_ASM("main/ssxapp", func_0022A830);

INCLUDE_ASM("main/ssxapp", func_0022ADD8);

INCLUDE_ASM("main/ssxapp", func_0022B008);

