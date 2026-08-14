#include "common.h"

// 16-byte array elements; indexing as arr[i].field (rather than manual
// pointer arithmetic) is what makes GCC emit the target's base-first addu
struct sGameEntry {
    int field_0x0;
    int field_0x4;
    int field_0x8;
    int field_0xc;
};
extern sGameEntry D_00442168[];

INCLUDE_ASM("main/game", cGame_renderModels);

INCLUDE_ASM("main/game", func_0022C1B0);

INCLUDE_ASM("main/game", func_0022C3B8);

INCLUDE_ASM("main/game", func_0022C410);

INCLUDE_ASM("main/game", cGame_renderPatches);

INCLUDE_ASM("main/game", cGame_renderFogVolumes);

INCLUDE_ASM("main/game", cGame_renderLightHalos);

INCLUDE_ASM("main/game", func_0022C830);

INCLUDE_ASM("main/game", func_0022CCE8);

INCLUDE_ASM("main/game", func_0022CD18);

INCLUDE_ASM("main/game", func_0022CD40);

INCLUDE_ASM("main/game", func_0022CEA8);

INCLUDE_ASM("main/game", func_0022D088);

INCLUDE_ASM("main/game", func_0022D278);

INCLUDE_ASM("main/game", func_0022D390);

INCLUDE_ASM("main/game", func_0022D3D8);

INCLUDE_ASM("main/game", func_0022D478);

INCLUDE_ASM("main/game", func_0022D598);

INCLUDE_ASM("main/game", func_0022D640);

INCLUDE_ASM("main/game", func_0022D668);

INCLUDE_ASM("main/game", func_0022D6C8);

INCLUDE_ASM("main/game", func_0022D8D8);

INCLUDE_ASM("main/game", func_0022DE58);

INCLUDE_ASM("main/game", func_0022DE98);

INCLUDE_ASM("main/game", func_0022DF50);

extern "C" void* func_002312D8(int);

//100%
INCLUDE_ASM("main/game", func_0022DFD0__FPv);
#ifdef SKIP_ASM
void* func_0022DFD0(void* self)
{
    return func_002312D8(*(int*)((char*)self + 0x1b0));
}
#endif

INCLUDE_ASM("main/game", func_0022DFF0);

//100%
INCLUDE_ASM("main/game", func_0022E078);
#ifdef SKIP_ASM
extern "C" int func_0022E078(void* self, int a1)
{
    int v = D_00442168[a1].field_0x8;
    return (unsigned int)(v - 1) < 2;
}
#endif

INCLUDE_ASM("main/game", func_0022E098);

//100%
INCLUDE_ASM("main/game", func_0022E0C8);
#ifdef SKIP_ASM
extern "C" int func_0022E0C8(void* self, int a1)
{
    return D_00442168[a1].field_0x4;
}
#endif

INCLUDE_ASM("main/game", func_0022E0E0);

