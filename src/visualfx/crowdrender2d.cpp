#include "visualfx/crowdrender2d.h"

INCLUDE_ASM("visualfx/crowdrender2d", cCrowdRender2D_cCrowdRender2D);
#ifdef SKIP_ASM
int cCrowdRender2D_cCrowdRender2D(int param_1) {
	cCrowdRender2D_init();
	return param_1;
}
#endif

INCLUDE_ASM("visualfx/crowdrender2d", cCrowdRender2D__cCrowdRender2D);
#ifdef SKIP_ASM
void cCrowdRender2D__cCrowdRender2D(int param_1)
{
	void* pvVar1;

	//pvVar1 = fun_00317d70(0x20, 0x4875d8, 0x20000000, 0);
	cCrowdAnim2D_cCrowdAnim2D(pvVar1, param_1);
	return;
}
#endif

INCLUDE_ASM("visualfx/crowdrender2d", cCrowdRender2D_init);
#ifdef SKIP_ASM
void cCrowdRender2D_init()
{

}
#endif

INCLUDE_ASM("visualfx/crowdrender2d", cCrowdRender2D_purge);

INCLUDE_ASM("visualfx/crowdrender2d", cCrowdRender2D_constructCrowdAnim2D);

INCLUDE_ASM("visualfx/crowdrender2d", cCrowdAnim2D_cCrowdAnim2D);
#ifdef SKIP_ASM
void cCrowdAnim2D_cCrowdAnim2D(void* pvVar1, int param_1)
{

}
#endif

INCLUDE_ASM("visualfx/crowdrender2d", cCrowdAnim2D_advanceFrame);

INCLUDE_ASM("visualfx/crowdrender2d", cCrowdAnim2D_update);

