#include "common.h"

extern int D_005305B0[];

struct sPlayerCharEntry {
    char pad_0x00[0x11];
    signed char mCharID; // 0x11
    char pad_0x12[0x1C - 0x11 - 1];
};
extern sPlayerCharEntry D_00534FE0[];

extern "C" void func_00145B20(void* self);
extern "C" void cBENewPlayerInterface_defaultCtrl(void* self);
extern void* D_0045AE28[16];

struct cBENewPlayerInterfaceCtor {
    char pad_0x00[8];
    int field_0x8;
    void* vtable;
};

//100%
INCLUDE_ASM("be/beintplayer", cBENewPlayerInterface_cBENewPlayerInterface__FP25cBENewPlayerInterfaceCtor);
#ifdef SKIP_ASM
cBENewPlayerInterfaceCtor* cBENewPlayerInterface_cBENewPlayerInterface(cBENewPlayerInterfaceCtor* self)
{
    self->field_0x8 = 0;
    self->vtable = D_0045AE28;
    func_00145B20(self);
    cBENewPlayerInterface_defaultCtrl(self);
    return self;
}
#endif

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern const char D_0045A1D8[];
extern void* D_004A11C0;

//99.24%
INCLUDE_ASM("be/beintplayer", cBENewPlayerInterface_getThis__Fv);
#ifdef SKIP_ASM
void* cBENewPlayerInterface_getThis()
{
    if (D_004A11C0 == 0) {
        void* mem = cMemMan_alloc(0x10, D_0045A1D8, 0, 0);
        D_004A11C0 = cBENewPlayerInterface_cBENewPlayerInterface((cBENewPlayerInterfaceCtor*)mem);
    }
    return D_004A11C0;
}
#endif

INCLUDE_ASM("be/beintplayer", func_001459B8);

INCLUDE_ASM("be/beintplayer", func_00145A98);

INCLUDE_ASM("be/beintplayer", func_00145B20);

INCLUDE_ASM("be/beintplayer", cBENewPlayerInterface_defaultCtrl);

INCLUDE_ASM("be/beintplayer", func_00145C38);

INCLUDE_ASM("be/beintplayer", func_00145CB0);

INCLUDE_ASM("be/beintplayer", func_00145D38);

INCLUDE_ASM("be/beintplayer", func_00145DD0);

INCLUDE_ASM("be/beintplayer", func_00145E68);

INCLUDE_ASM("be/beintplayer", func_00145EF0);

INCLUDE_ASM("be/beintplayer", cBENewPlayerInterface_isPeakLocked);

INCLUDE_ASM("be/beintplayer", cBENewPlayerInterface_isPeakLocked1);

INCLUDE_ASM("be/beintplayer", func_00146150);

INCLUDE_ASM("be/beintplayer", func_00146320);

INCLUDE_ASM("be/beintplayer", func_001464D0);

INCLUDE_ASM("be/beintplayer", func_00146A70);

INCLUDE_ASM("be/beintplayer", func_00146D98);

INCLUDE_ASM("be/beintplayer", func_00146E10);

INCLUDE_ASM("be/beintplayer", func_00146E98);

INCLUDE_ASM("be/beintplayer", func_00146F88);

INCLUDE_ASM("be/beintplayer", func_00147138);

INCLUDE_ASM("be/beintplayer", func_00147170);

INCLUDE_ASM("be/beintplayer", cBENewPlayerInterface_setRiderCtrlID);

INCLUDE_ASM("be/beintplayer", func_00147290);

INCLUDE_ASM("be/beintplayer", func_001472C8);

INCLUDE_ASM("be/beintplayer", func_00147318);

INCLUDE_ASM("be/beintplayer", cBENewPlayerInterface_setRiderCharID);

int cBENewPlayerInterface_getPlayerID(int index);

//100%
INCLUDE_ASM("be/beintplayer", cBENewPlayerInterface_getRiderCharID__FPvi);
#ifdef SKIP_ASM
signed char cBENewPlayerInterface_getRiderCharID(void* self, int riderIndex)
{
    int playerID = cBENewPlayerInterface_getPlayerID(riderIndex);
    sPlayerCharEntry* entry = &D_00534FE0[playerID];
    return entry->mCharID;
}
#endif

INCLUDE_ASM("be/beintplayer", func_001473D0);

INCLUDE_ASM("be/beintplayer", func_00147410);

INCLUDE_ASM("be/beintplayer", func_00147448);

//100%
INCLUDE_ASM("be/beintplayer", cBENewPlayerInterface_getPlayerCharID__FPvi);
#ifdef SKIP_ASM
signed char cBENewPlayerInterface_getPlayerCharID(void* self, int index)
{
    index *= sizeof(sPlayerCharEntry);
    return ((sPlayerCharEntry*)((char*)D_00534FE0 + index))->mCharID;
}
#endif

INCLUDE_ASM("be/beintplayer", func_001474A8);

INCLUDE_ASM("be/beintplayer", func_001474C8);

INCLUDE_ASM("be/beintplayer", func_001474E8);

INCLUDE_ASM("be/beintplayer", func_00147528);

INCLUDE_ASM("be/beintplayer", func_00147580);

INCLUDE_ASM("be/beintplayer", func_001475C0);

INCLUDE_ASM("be/beintplayer", func_00147618);

INCLUDE_ASM("be/beintplayer", func_00147658);

//100%
INCLUDE_ASM("be/beintplayer", cBENewPlayerInterface_getPlayerID__Fi);
#ifdef SKIP_ASM
int cBENewPlayerInterface_getPlayerID(int index)
{
    return D_005305B0[index];
}
#endif

//96%
INCLUDE_ASM("be/beintplayer", cBENewPlayerInterface_isMissionMan__Fi);
#ifdef SKIP_ASM
int cBENewPlayerInterface_isMissionMan(int index)
{
    int playerID = cBENewPlayerInterface_getPlayerID(index);
    char* entry = (char*)D_00534FE0 + playerID * 0x1C;
    int flags = *(int*)(entry + 0x10);
    return (flags >> 2) & 1;
}
#endif

INCLUDE_ASM("be/beintplayer", func_00147828);

INCLUDE_ASM("be/beintplayer", cBENewPlayerInterface_resetFromMissionMan);

INCLUDE_ASM("be/beintplayer", func_00147908);

INCLUDE_ASM("be/beintplayer", func_00147980);

INCLUDE_ASM("be/beintplayer", func_00147A30);

INCLUDE_ASM("be/beintplayer", func_00147CB8);

INCLUDE_ASM("be/beintplayer", func_00147D20);

INCLUDE_ASM("be/beintplayer", func_00147E18);

INCLUDE_ASM("be/beintplayer", func_00147F78);

INCLUDE_ASM("be/beintplayer", func_00147FD8);

INCLUDE_ASM("be/beintplayer", func_00148098);

INCLUDE_ASM("be/beintplayer", func_00148158);

INCLUDE_ASM("be/beintplayer", func_001483A0);

INCLUDE_ASM("be/beintplayer", func_00148410);

INCLUDE_ASM("be/beintplayer", func_00148470);

INCLUDE_ASM("be/beintplayer", func_001484E0);

INCLUDE_ASM("be/beintplayer", func_00148540);

INCLUDE_ASM("be/beintplayer", func_001485B0);

INCLUDE_ASM("be/beintplayer", func_00148610);

INCLUDE_ASM("be/beintplayer", func_00148680);

INCLUDE_ASM("be/beintplayer", func_001486E0);

INCLUDE_ASM("be/beintplayer", func_00148750);

INCLUDE_ASM("be/beintplayer", func_001487B0);

INCLUDE_ASM("be/beintplayer", func_00148820);

INCLUDE_ASM("be/beintplayer", func_00148880);

INCLUDE_ASM("be/beintplayer", func_001488F0);

INCLUDE_ASM("be/beintplayer", func_00148950);

INCLUDE_ASM("be/beintplayer", func_00148AA8);

INCLUDE_ASM("be/beintplayer", func_00148B78);

INCLUDE_ASM("be/beintplayer", func_00148BC8);

INCLUDE_ASM("be/beintplayer", func_00148C18);

INCLUDE_ASM("be/beintplayer", func_00148C68);

INCLUDE_ASM("be/beintplayer", func_00148CB8);

INCLUDE_ASM("be/beintplayer", func_00148D08);

INCLUDE_ASM("be/beintplayer", func_00148D58);

INCLUDE_ASM("be/beintplayer", func_00148D80);

INCLUDE_ASM("be/beintplayer", func_00148E68);

