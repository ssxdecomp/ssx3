#include "common.h"

INCLUDE_ASM("fe/festatecharsetup", cFEStateCharSetup_onCreateScreen);

INCLUDE_ASM("fe/festatecharsetup", func_00182C08);

INCLUDE_ASM("fe/festatecharsetup", func_00182C38);

//100%
INCLUDE_ASM("fe/festatecharsetup", func_00182C68);
#ifdef SKIP_ASM
extern "C" int func_00182C68(void* self, int a1, int a2)
{
    return a2 != 9 ? 0x101 : 0x100;
}
#endif

INCLUDE_ASM("fe/festatecharsetup", func_00182C80);

INCLUDE_ASM("fe/festatecharsetup", func_00182DB8);

INCLUDE_ASM("fe/festatecharsetup", func_00182EC0);

INCLUDE_ASM("fe/festatecharsetup", func_001831D0);

INCLUDE_ASM("fe/festatecharsetup", func_00183238);

