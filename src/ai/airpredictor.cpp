#include "common.h"

INCLUDE_ASM("ai/airpredictor", cAirPredictor_reset);

INCLUDE_ASM("ai/airpredictor", func_00113200);

INCLUDE_ASM("ai/airpredictor", cAirPredictor_startLaunchIntoAir);

struct sQuad {
    int x[4];
};

//0% - wrong copy idiom (lq/sq vs target's unaligned ldl/ldr,sdl/sdr); logic correct, codegen mismatch unresolved
INCLUDE_ASM("ai/airpredictor", cAirPredictor_initLaunch__FPcP5sQuadT1);
#ifdef SKIP_ASM
void cAirPredictor_initLaunch(char* self, sQuad* a, sQuad* b)
{
    *(int*)(self + 0xAC) = 0;
    float f = *(float*)(self + 0xA0);
    *(sQuad*)(self + 0x70) = *a;
    *(sQuad*)(self + 0x80) = *b;
    *(sQuad*)(self + 0x50) = *a;
    *(float*)(self + 0x98) = f;
    *(sQuad*)(self + 0x60) = *b;
}
#endif

INCLUDE_ASM("ai/airpredictor", func_00113648);

INCLUDE_ASM("ai/airpredictor", func_00113998);

INCLUDE_ASM("ai/airpredictor", func_001139A0);

INCLUDE_ASM("ai/airpredictor", func_00113AA0);

INCLUDE_ASM("ai/airpredictor", func_00113AD8);

