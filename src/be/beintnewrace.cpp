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

// padded past the 8-byte gp-relative threshold so the compiler emits
// absolute lui/lo addressing like the target, instead of assuming small data
struct sD_00535C08 { int value; int pad[2]; };
extern sD_00535C08 D_00535C08;

// padded past the 8-byte gp-relative threshold so the compiler emits
// absolute lui/lo addressing like the target, instead of assuming small data
struct sPad16 { char x; int pad[3]; };
extern sPad16 D_0043D984;

extern sPad16 D_0043D954;

// 0x64-byte array elements; arr[i].field indexing is what makes GCC emit the
// target's base-first addu (manual pointer arithmetic reverses the operands)
struct sRaceEntry {
    char pad_0x00[0x54];
    int field_0x54;
    int field_0x58;
    char pad_0x5c[4];
    int field_0x60;
};
extern sRaceEntry D_0043D950[];

extern sPad16 D_0043E254;

struct sRaceEntry18 {
    char pad_0x00[0x14];
    int field_0x14;
};
extern sRaceEntry18 D_0043E250[];

extern sPad16 D_0043E7D0;

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

//100%
INCLUDE_ASM("be/beintnewrace", func_00144BC0);
#ifdef SKIP_ASM
extern "C" void* func_00144BC0()
{
    return (char*)&D_0043D950[0] + D_00535C08.value * 0x64;
}
#endif

//100%
INCLUDE_ASM("be/beintnewrace", func_00144BE0);
#ifdef SKIP_ASM
extern "C" int func_00144BE0()
{
    return D_00535C08.value;
}
#endif

//100%
INCLUDE_ASM("be/beintnewrace", func_00144BF0);
#ifdef SKIP_ASM
extern "C" void* func_00144BF0()
{
    return (char*)&D_0043D954 + D_00535C08.value * 0x64;
}
#endif

//100%
INCLUDE_ASM("be/beintnewrace", func_00144C48);
#ifdef SKIP_ASM
extern "C" void* func_00144C48(void* self, int a1)
{
    return (char*)&D_0043D984 + a1 * 0x64;
}
#endif

//100%
INCLUDE_ASM("be/beintnewrace", func_00144C60);
#ifdef SKIP_ASM
extern "C" void* func_00144C60(void* self, int a1)
{
    return (char*)&D_0043D954 + a1 * 0x64;
}
#endif

//100%
INCLUDE_ASM("be/beintnewrace", func_00144C78);
#ifdef SKIP_ASM
extern "C" int func_00144C78(void* self, int a1)
{
    return D_0043D950[a1].field_0x54;
}
#endif

//100%
INCLUDE_ASM("be/beintnewrace", func_00144C98);
#ifdef SKIP_ASM
extern "C" int func_00144C98()
{
    return D_0043D950[D_00535C08.value].field_0x54;
}
#endif

//100%
INCLUDE_ASM("be/beintnewrace", func_00144CC0);
#ifdef SKIP_ASM
extern "C" int func_00144CC0(void* self, int a1)
{
    return D_0043D950[a1].field_0x58;
}
#endif

INCLUDE_ASM("be/beintnewrace", func_00144CE0);

//100%
INCLUDE_ASM("be/beintnewrace", func_00144D18);
#ifdef SKIP_ASM
extern "C" int func_00144D18(void* self, int a1)
{
    return D_0043D950[a1].field_0x60;
}
#endif

//100%
INCLUDE_ASM("be/beintnewrace", func_00144D38);
#ifdef SKIP_ASM
extern "C" void* func_00144D38(void* self, int a1)
{
    return (char*)&D_0043E254 + a1 * 0x18;
}
#endif

//100%
INCLUDE_ASM("be/beintnewrace", func_00144D50);
#ifdef SKIP_ASM
extern "C" int func_00144D50(void* self, int a1)
{
    return D_0043E250[a1].field_0x14;
}
#endif

//100%
INCLUDE_ASM("be/beintnewrace", func_00144D70__FPvii);
#ifdef SKIP_ASM
void* func_00144D70(void* self, int a1, int a2)
{
    *(int*)((char*)(void*)&D_00535BC8 + a1 * 4) = a2;
    *(int*)((char*)((char*)(void*)&D_00535BC8 + a2 * 4) + 0x18) = a1;
    return ((char*)(void*)&D_00535BC8 + a1 * 4);
}
#endif

INCLUDE_ASM("be/beintnewrace", cBENewRaceInterface_setNumberAI);

INCLUDE_ASM("be/beintnewrace", cBENewRaceInterface_setGameMode);

INCLUDE_ASM("be/beintnewrace", func_00145108);

INCLUDE_ASM("be/beintnewrace", cBENewRaceInterface_setGameEvent);

INCLUDE_ASM("be/beintnewrace", func_00145340);

INCLUDE_ASM("be/beintnewrace", func_00145378);

INCLUDE_ASM("be/beintnewrace", func_00145398);

//100%
INCLUDE_ASM("be/beintnewrace", func_001453B8);
#ifdef SKIP_ASM
extern "C" void* func_001453B8(void* self, int a1)
{
    return (char*)&D_0043E7D0 + a1 * 0x3c;
}
#endif

INCLUDE_ASM("be/beintnewrace", func_001453D0);

INCLUDE_ASM("be/beintnewrace", func_001454F8);

INCLUDE_ASM("be/beintnewrace", func_001455D0);

INCLUDE_ASM("be/beintnewrace", func_00145600);

INCLUDE_ASM("be/beintnewrace", func_00145630);

INCLUDE_ASM("be/beintnewrace", func_00145668);

INCLUDE_ASM("be/beintnewrace", func_001456A0);

INCLUDE_ASM("be/beintnewrace", func_00145750);

INCLUDE_ASM("be/beintnewrace", func_00145870);

