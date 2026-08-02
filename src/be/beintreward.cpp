#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern const char D_0045A938[];
extern void* D_0045AE88[16];
extern void* D_004A1264;

struct cBERewardInterface {
    char pad_0x00[8];
    int field_0x8;
    void* vtable;
};

//99.84%
INCLUDE_ASM("be/beintreward", cBERewardInterface_getThis__Fv);
#ifdef SKIP_ASM
void* cBERewardInterface_getThis()
{
    if (D_004A1264 == 0) {
        cBERewardInterface* mem = (cBERewardInterface*)cMemMan_alloc(0x18, D_0045A938, 0, 0);
        mem->field_0x8 = 0;
        mem->vtable = D_0045AE88;
        D_004A1264 = mem;
    }
    return D_004A1264;
}
#endif

INCLUDE_ASM("be/beintreward", func_00156A10);

INCLUDE_ASM("be/beintreward", func_00156A38);

//100%
INCLUDE_ASM("be/beintreward", cBERewardInterface_isBetterMedal__FPvii);
#ifdef SKIP_ASM
int cBERewardInterface_isBetterMedal(void* self, int a, int b)
{
    if (b == -1) {
        return 0;
    }
    if (a == -1) {
        return 1;
    }
    return b < a;
}
#endif

INCLUDE_ASM("be/beintreward", func_00156A90);

INCLUDE_ASM("be/beintreward", func_00156AE0);

INCLUDE_ASM("be/beintreward", func_00156B28);

INCLUDE_ASM("be/beintreward", func_00156C70);

INCLUDE_ASM("be/beintreward", func_00156EE0);

INCLUDE_ASM("be/beintreward", func_00157080);

INCLUDE_ASM("be/beintreward", func_00157210);

INCLUDE_ASM("be/beintreward", func_001572B0);

INCLUDE_ASM("be/beintreward", func_001572D0);

INCLUDE_ASM("be/beintreward", func_001572F0);

INCLUDE_ASM("be/beintreward", func_00157310);

INCLUDE_ASM("be/beintreward", func_00157330);

INCLUDE_ASM("be/beintreward", func_00157350);

INCLUDE_ASM("be/beintreward", func_00157370);

INCLUDE_ASM("be/beintreward", func_00157390);

INCLUDE_ASM("be/beintreward", func_001573F0);

INCLUDE_ASM("be/beintreward", func_00157430);

INCLUDE_ASM("be/beintreward", func_00157468);

INCLUDE_ASM("be/beintreward", func_00157518);

INCLUDE_ASM("be/beintreward", func_001575C0);

INCLUDE_ASM("be/beintreward", func_00157620);

INCLUDE_ASM("be/beintreward", func_00157680);

INCLUDE_ASM("be/beintreward", func_001576E0);

INCLUDE_ASM("be/beintreward", func_00157740);

INCLUDE_ASM("be/beintreward", func_001577A0);

INCLUDE_ASM("be/beintreward", func_001577E0);

INCLUDE_ASM("be/beintreward", func_001578A0);

INCLUDE_ASM("be/beintreward", func_00157920);

INCLUDE_ASM("be/beintreward", func_00157A78);

INCLUDE_ASM("be/beintreward", func_00157B08);

INCLUDE_ASM("be/beintreward", func_00157B70);

INCLUDE_ASM("be/beintreward", func_00157BF0);

INCLUDE_ASM("be/beintreward", func_00157D60);

INCLUDE_ASM("be/beintreward", func_00157DA0);

INCLUDE_ASM("be/beintreward", func_00157DE0);

INCLUDE_ASM("be/beintreward", func_00157E20);

INCLUDE_ASM("be/beintreward", func_00157E60);

INCLUDE_ASM("be/beintreward", func_00157EE0);

INCLUDE_ASM("be/beintreward", func_00157F20);

INCLUDE_ASM("be/beintreward", func_00157FD0);

INCLUDE_ASM("be/beintreward", func_001580F8);

INCLUDE_ASM("be/beintreward", func_00158220);

INCLUDE_ASM("be/beintreward", func_00158348);

INCLUDE_ASM("be/beintreward", func_00158470);

INCLUDE_ASM("be/beintreward", func_00158558);

INCLUDE_ASM("be/beintreward", func_00158618);

INCLUDE_ASM("be/beintreward", func_00158700);

INCLUDE_ASM("be/beintreward", func_00158728);

INCLUDE_ASM("be/beintreward", func_00158750);

INCLUDE_ASM("be/beintreward", func_001587B8);

INCLUDE_ASM("be/beintreward", func_001587F8);

INCLUDE_ASM("be/beintreward", func_00158820);

INCLUDE_ASM("be/beintreward", func_00158848);

INCLUDE_ASM("be/beintreward", func_00158870);

INCLUDE_ASM("be/beintreward", func_00158890);

INCLUDE_ASM("be/beintreward", func_001588B0);

void* cBECharProfileDB_getScoreStats(void* self, int a, int b);
extern int D_004A6CA8[];

//88.68%
INCLUDE_ASM("be/beintreward", cBERewardInterface_getTrackMedal__FPviiii);
#ifdef SKIP_ASM
signed char cBERewardInterface_getTrackMedal(void* self, int b, int c, int d, int e)
{
    char* ptr = (char*)D_004A6CA8 + c * 0xF88 + b * 0x9B50;
    void* result = cBECharProfileDB_getScoreStats(ptr, e, d);
    if (result == 0) {
        return -1;
    }
    return ((signed char*)result)[1];
}
#endif

INCLUDE_ASM("be/beintreward", func_00158960);

INCLUDE_ASM("be/beintreward", func_001589B0);

INCLUDE_ASM("be/beintreward", func_00158A50);

INCLUDE_ASM("be/beintreward", cBERewardInterface_getEarningsMedal);

INCLUDE_ASM("be/beintreward", func_00158BE0);

INCLUDE_ASM("be/beintreward", func_00158C80);

INCLUDE_ASM("be/beintreward", func_00158D58);

INCLUDE_ASM("be/beintreward", func_00158E30);

INCLUDE_ASM("be/beintreward", func_00158F20);

INCLUDE_ASM("be/beintreward", func_00158F30);

INCLUDE_ASM("be/beintreward", func_00158F60);

INCLUDE_ASM("be/beintreward", func_00159080);

INCLUDE_ASM("be/beintreward", func_00159170);

INCLUDE_ASM("be/beintreward", func_001591E8);

INCLUDE_ASM("be/beintreward", func_001597B0);

INCLUDE_ASM("be/beintreward", func_00159818);

INCLUDE_ASM("be/beintreward", func_001599A0);

INCLUDE_ASM("be/beintreward", func_00159B08);

INCLUDE_ASM("be/beintreward", func_00159CD0);

INCLUDE_ASM("be/beintreward", func_0015A2E0);

INCLUDE_ASM("be/beintreward", func_0015A320);

INCLUDE_ASM("be/beintreward", func_0015A358);

INCLUDE_ASM("be/beintreward", func_0015A398);

INCLUDE_ASM("be/beintreward", func_0015A3B8);

INCLUDE_ASM("be/beintreward", func_0015A478);

INCLUDE_ASM("be/beintreward", func_0015A488);

INCLUDE_ASM("be/beintreward", func_0015A510);

INCLUDE_ASM("be/beintreward", func_0015A5B0);

INCLUDE_ASM("be/beintreward", func_0015A5F0);

INCLUDE_ASM("be/beintreward", func_0015A628);

INCLUDE_ASM("be/beintreward", func_0015A6F0);

INCLUDE_ASM("be/beintreward", func_0015A750);

INCLUDE_ASM("be/beintreward", func_0015A768);

INCLUDE_ASM("be/beintreward", func_0015A778);

INCLUDE_ASM("be/beintreward", func_0015A7D0);

INCLUDE_ASM("be/beintreward", func_0015A818);

