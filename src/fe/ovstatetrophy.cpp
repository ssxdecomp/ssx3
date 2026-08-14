#include "common.h"

INCLUDE_ASM("fe/ovstatetrophy", cOVStateTrophy_onCreateScreen);

INCLUDE_ASM("fe/ovstatetrophy", func_0020E9A0);

INCLUDE_ASM("fe/ovstatetrophy", func_0020EAA0);

INCLUDE_ASM("fe/ovstatetrophy", func_0020EB08);

INCLUDE_ASM("fe/ovstatetrophy", func_0020EB50);

INCLUDE_ASM("fe/ovstatetrophy", func_0020EC18);

INCLUDE_ASM("fe/ovstatetrophy", func_0020ED20);

INCLUDE_ASM("fe/ovstatetrophy", func_0020EDA0);

INCLUDE_ASM("fe/ovstatetrophy", func_0020FB40);

struct sPad16 { char x; int pad[3]; };
extern sPad16 D_004C8BC8;

//100%
INCLUDE_ASM("fe/ovstatetrophy", func_002105B0);
#ifdef SKIP_ASM
extern "C" void func_002105B0(int a0)
{
    char* p = (char*)&D_004C8BC8 + a0 * 0x18;
    *(int*)p = 1;
}
#endif

INCLUDE_ASM("fe/ovstatetrophy", func_002105D0);

INCLUDE_ASM("fe/ovstatetrophy", func_00210608);

INCLUDE_ASM("fe/ovstatetrophy", func_00210618);

INCLUDE_ASM("fe/ovstatetrophy", func_00210820);

INCLUDE_ASM("fe/ovstatetrophy", func_002108F8);

INCLUDE_ASM("fe/ovstatetrophy", func_00210940);

INCLUDE_ASM("fe/ovstatetrophy", func_00210B58);

INCLUDE_ASM("fe/ovstatetrophy", func_00210BD8);

INCLUDE_ASM("fe/ovstatetrophy", func_00210D20);

//100%
INCLUDE_ASM("fe/ovstatetrophy", func_00210DD0);
#ifdef SKIP_ASM
extern "C" void func_00210DD0(void* self, int a1, int a2)
{
    if (a2 == 0x16) {
        if (a1 == *(int*)((char*)self + 0xe0)) {
            *(int*)((char*)self + 0xe0) = 0;
        }
    }
}
#endif

INCLUDE_ASM("fe/ovstatetrophy", func_00210DF0);

INCLUDE_ASM("fe/ovstatetrophy", func_00210F40);

INCLUDE_ASM("fe/ovstatetrophy", func_00210FA0);

INCLUDE_ASM("fe/ovstatetrophy", func_00211088);

