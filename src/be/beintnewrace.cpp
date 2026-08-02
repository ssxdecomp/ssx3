#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern const char D_0045A0F0[];
extern void* D_0045AE58[16];
extern void* D_004A11B4;

struct cBENewRaceInterface {
    char pad_0x00[8];
    int field_0x8;
    void* vtable;
};

struct sRaceInterfaceGlobal {
    int arr1[6]; // 0x0
    int arr2[6]; // 0x18
    int field_0x30;
    int field_0x34;
    int field_0x38;
    int field_0x3C;
};
extern sRaceInterfaceGlobal D_00535BC8;

//99.58%
INCLUDE_ASM("be/beintnewrace", cBENewRaceInterface_getThis__Fv);
#ifdef SKIP_ASM
void* cBENewRaceInterface_getThis()
{
    if (D_004A11B4 == 0) {
        cBENewRaceInterface* mem = (cBENewRaceInterface*)cMemMan_alloc(0x10, D_0045A0F0, 0, 0);
        mem->field_0x8 = 0;
        mem->vtable = D_0045AE58;
        D_004A11B4 = mem;
    }
    return D_004A11B4;
}
#endif

INCLUDE_ASM("be/beintnewrace", func_00144928);

INCLUDE_ASM("be/beintnewrace", func_001449E8);

//63.16% - target uses an up-counting loop with slti; ours keeps compiling to a down-counting or bne-based loop despite several rewrites
INCLUDE_ASM("be/beintnewrace", cBENewRaceInterface_setNumberHumans__FPvi);
#ifdef SKIP_ASM
void cBENewRaceInterface_setNumberHumans(void* self, int humans)
{
    D_00535BC8.field_0x34 = humans;
    D_00535BC8.field_0x30 = humans + D_00535BC8.field_0x3C + D_00535BC8.field_0x38;
    int* p = (int*)&D_00535BC8;
    int i = 0;
    while (i != 6) {
        p[0] = 0;
        p[6] = 0;
        i++;
        p++;
    }
}
#endif

//100%
INCLUDE_ASM("be/beintnewrace", cBENewRaceInterface_setNumberMission__FPvi);
#ifdef SKIP_ASM
void cBENewRaceInterface_setNumberMission(void* self, int mission)
{
    int a = D_00535BC8.field_0x34;
    int b = D_00535BC8.field_0x3C;
    D_00535BC8.field_0x38 = mission;
    D_00535BC8.field_0x30 = a + b + mission;
}
#endif

INCLUDE_ASM("be/beintnewrace", func_00144B20);

INCLUDE_ASM("be/beintnewrace", func_00144BC0);

INCLUDE_ASM("be/beintnewrace", func_00144BE0);

INCLUDE_ASM("be/beintnewrace", func_00144BF0);

INCLUDE_ASM("be/beintnewrace", func_00144C48);

INCLUDE_ASM("be/beintnewrace", func_00144C60);

INCLUDE_ASM("be/beintnewrace", func_00144C78);

INCLUDE_ASM("be/beintnewrace", func_00144C98);

INCLUDE_ASM("be/beintnewrace", func_00144CC0);

INCLUDE_ASM("be/beintnewrace", func_00144CE0);

INCLUDE_ASM("be/beintnewrace", func_00144D18);

INCLUDE_ASM("be/beintnewrace", func_00144D38);

INCLUDE_ASM("be/beintnewrace", func_00144D50);

INCLUDE_ASM("be/beintnewrace", func_00144D70);

INCLUDE_ASM("be/beintnewrace", cBENewRaceInterface_setNumberAI);

INCLUDE_ASM("be/beintnewrace", cBENewRaceInterface_setGameMode);

INCLUDE_ASM("be/beintnewrace", func_00145108);

INCLUDE_ASM("be/beintnewrace", cBENewRaceInterface_setGameEvent);

INCLUDE_ASM("be/beintnewrace", func_00145340);

INCLUDE_ASM("be/beintnewrace", func_00145378);

INCLUDE_ASM("be/beintnewrace", func_00145398);

INCLUDE_ASM("be/beintnewrace", func_001453B8);

INCLUDE_ASM("be/beintnewrace", func_001453D0);

INCLUDE_ASM("be/beintnewrace", func_001454F8);

INCLUDE_ASM("be/beintnewrace", func_001455D0);

INCLUDE_ASM("be/beintnewrace", func_00145600);

INCLUDE_ASM("be/beintnewrace", func_00145630);

INCLUDE_ASM("be/beintnewrace", func_00145668);

INCLUDE_ASM("be/beintnewrace", func_001456A0);

INCLUDE_ASM("be/beintnewrace", func_00145750);

INCLUDE_ASM("be/beintnewrace", func_00145870);

