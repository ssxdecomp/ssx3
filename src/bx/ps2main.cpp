#include "common.h"

INCLUDE_ASM("bx/ps2main", systemInit);

INCLUDE_ASM("bx/ps2main", main);

INCLUDE_ASM("bx/ps2main", func_0031B008);

//100%
INCLUDE_ASM("bx/ps2main", func_0031B088);
#ifdef SKIP_ASM
extern "C" float func_0031B088(float a, float b, float c, float d)
{
    return a * d - b * c;
}
#endif

INCLUDE_ASM("bx/ps2main", func_0031B098);

INCLUDE_ASM("bx/ps2main", func_0031B178);

INCLUDE_ASM("bx/ps2main", func_0031B310);

INCLUDE_ASM("bx/ps2main", func_0031B6C8);

INCLUDE_ASM("bx/ps2main", func_0031B748);

INCLUDE_ASM("bx/ps2main", func_0031B7A8);

INCLUDE_ASM("bx/ps2main", func_0031BB30);

INCLUDE_ASM("bx/ps2main", func_0031BCB0);

INCLUDE_ASM("bx/ps2main", func_0031BE50);

INCLUDE_ASM("bx/ps2main", func_0031BF60);

INCLUDE_ASM("bx/ps2main", func_0031C040);

INCLUDE_ASM("bx/ps2main", func_0031C128);

INCLUDE_ASM("bx/ps2main", func_0031C228);

