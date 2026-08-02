#include "common.h"

INCLUDE_ASM("render/ps2graphicsman", cPSPGraphicsMan_NewNonBindTexID);

INCLUDE_ASM("render/ps2graphicsman", func_003671C8);

INCLUDE_ASM("render/ps2graphicsman", func_00367230);

INCLUDE_ASM("render/ps2graphicsman", cPSPGraphicsMan_NewBindTexID);

INCLUDE_ASM("render/ps2graphicsman", func_003672C0);

INCLUDE_ASM("render/ps2graphicsman", func_00367310);

extern "C" void* func_00365E40(void*, int, int, void*);

//100%
INCLUDE_ASM("render/ps2graphicsman", func_00367340__FPvii);
#ifdef SKIP_ASM
void* func_00367340(void* self, int a1, int a2)
{
    return func_00365E40((char*)self + 0x4350, a1, a2, (char*)self + 0x8);
}
#endif

INCLUDE_ASM("render/ps2graphicsman", func_00367360);

//100%
INCLUDE_ASM("render/ps2graphicsman", func_003673D0__FPv);
#ifdef SKIP_ASM
void func_003673D0(void* self)
{
}
#endif

INCLUDE_ASM("render/ps2graphicsman", func_003673D8);

INCLUDE_ASM("render/ps2graphicsman", func_00367440);

INCLUDE_ASM("render/ps2graphicsman", func_00367B60);

INCLUDE_ASM("render/ps2graphicsman", func_00367BC0);

INCLUDE_ASM("render/ps2graphicsman", func_00367CD0);

INCLUDE_ASM("render/ps2graphicsman", func_00367D20);

INCLUDE_ASM("render/ps2graphicsman", func_00367DB8);

INCLUDE_ASM("render/ps2graphicsman", func_00367F18);

INCLUDE_ASM("render/ps2graphicsman", func_00368138);

INCLUDE_ASM("render/ps2graphicsman", func_00368170);

INCLUDE_ASM("render/ps2graphicsman", func_003684F0);

INCLUDE_ASM("render/ps2graphicsman", func_00368660);

INCLUDE_ASM("render/ps2graphicsman", func_00368970);

INCLUDE_ASM("render/ps2graphicsman", func_00369098);

INCLUDE_ASM("render/ps2graphicsman", func_00369130);

INCLUDE_ASM("render/ps2graphicsman", func_003691B0);

INCLUDE_ASM("render/ps2graphicsman", func_003691F8);

INCLUDE_ASM("render/ps2graphicsman", func_003695D8);

INCLUDE_ASM("render/ps2graphicsman", func_00369610);

INCLUDE_ASM("render/ps2graphicsman", func_00369690);

INCLUDE_ASM("render/ps2graphicsman", func_003696C8);

//100%
INCLUDE_ASM("render/ps2graphicsman", func_00369890__FPvii);
#ifdef SKIP_ASM
void func_00369890(void* self, int a1, int a2)
{
    *(int*)((char*)self + 0x27c) = a2;
    *(int*)((char*)self + 0x278) = a1;
    *(int*)((char*)self + 0xe80) = 0;
}
#endif

INCLUDE_ASM("render/ps2graphicsman", func_003698A0);

