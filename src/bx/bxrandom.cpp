#include "common.h"
void cBxPseudoRng_Seed(uint* param_1, uint seedAddend);
void BXsrand(uint seed);
extern const uint D_004FF018[];

//100%
//https://decomp.me/scratch/ViFdz
INCLUDE_ASM("bx/bxrandom", BXsrand__FUi);
#ifdef SKIP_ASM
void BXsrand(uint seed)
{
	cBxPseudoRng_Seed((uint*)D_004FF018, seed);
	return;
}
#endif

INCLUDE_ASM("bx/bxrandom", BXrand__Fv);
#ifdef SKIP_ASM
unsigned int cBxPseudoRng_NextInt(const uint[]);                         /* extern */

void BXrand()
{
    cBxPseudoRng_NextInt(D_004FF018);
}
#endif


//100%
INCLUDE_ASM("bx/bxrandom", AIrand__Fv);
#ifdef SKIP_ASM
extern const uint D_004FF030[];

unsigned int AIrand()
{
    return cBxPseudoRng_NextInt(D_004FF030);
}
#endif

INCLUDE_ASM("bx/bxrandom", AIrandf__Fff);
#ifdef SKIP_ASM
unsigned int AIrand();

float AIrandf(float a, float b)
{
	unsigned int r = (AIrand() & 0x7FFFFFFF) | 0x3F800000;
	float f = *((float*)&r) - 1.0f; // random 0.0 ? f < 1.0
	return a + (b - a) * f;
}
#endif

INCLUDE_ASM("bx/bxrandom", func_00317890__Fff);
#ifdef SKIP_ASM
float func_00317890(float param_1, float param_2)
{
	float fVar1;

	fVar1 = AIrandf(-1.0, 1.0);
	return param_1 + param_2 * fVar1;
}
#endif

INCLUDE_ASM("bx/bxrandom", func_003178E0);

INCLUDE_ASM("bx/bxrandom", func_00317908);

INCLUDE_ASM("bx/bxrandom", func_00317930);

INCLUDE_ASM("bx/bxrandom", cBxPseudoRng_Seed);

INCLUDE_ASM("bx/bxrandom", cBxPseudoRng_NextInt);
