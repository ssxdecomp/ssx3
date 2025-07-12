#include "visualfx/crowdrender2d.h"

//100%
//https://decomp.me/scratch/pOTwa

INCLUDE_ASM("visualfx/crowdrender2d", cCrowdRender2D_cCrowdRender2D__Fi);
#ifdef SKIP_ASM
int cCrowdRender2D_cCrowdRender2D(int param_1) {
	cCrowdRender2D_init();
	return param_1;
}
#endif

//100%
//https://decomp.me/scratch/zsTkS

INCLUDE_ASM("visualfx/crowdrender2d", cCrowdRender2D__cCrowdRender2D__FPii);
#ifdef SKIP_ASM
void cCrowdRender2D__cCrowdRender2D(int* param_1, int param_2)
{
	cCrowdRender2D_purge(param_1);

	if ((param_2 & 1) != 0) {
		operator_delete(param_1);
	}

	return;
}
#endif

INCLUDE_ASM("visualfx/crowdrender2d", cCrowdRender2D_init__Fv);
#ifdef SKIP_ASM
void cCrowdRender2D_init()
{

}
#endif

INCLUDE_ASM("visualfx/crowdrender2d", cCrowdRender2D_purge__FPi);
#ifdef SKIP_ASM
int cCrowdRender2D_purge(int *param_1)
{
	return *param_1;
}
#endif

//100%
//https://decomp.me/scratch/Rbiv4
INCLUDE_ASM("visualfx/crowdrender2d", cCrowdRender2D_constructCrowdAnim2D);
#ifdef SKIP_ASM
void* cCrowdRender2D_constructCrowdAnim2D(void* param) {
	void* memory = cMemMan_alloc(0x20, D_004875D8, 0x20000000, 0);
	return cCrowdAnim2D_cCrowdAnim2D(memory, param);
}
#endif

INCLUDE_ASM("visualfx/crowdrender2d", cCrowdAnim2D_cCrowdAnim2D);
#ifdef SKIP_ASM
void cCrowdAnim2D_cCrowdAnim2D(void* pvVar1, int param_1)
{

}
#endif

INCLUDE_ASM("visualfx/crowdrender2d", cCrowdAnim2D_advanceFrame);

INCLUDE_ASM("visualfx/crowdrender2d", cCrowdAnim2D_update);

