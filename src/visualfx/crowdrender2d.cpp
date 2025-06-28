#include "visualfx/crowdrender2d.h"

namespace cCrowdRender2D
{
	INCLUDE_ASM("visualfx/crowdrender2d", cCrowdRender2D_cCrowdRender2D);
	int cCrowdRender2D_cCrowdRender2D(int param_1) {
		init();
		return param_1;
	}

	INCLUDE_ASM("visualfx/crowdrender2d", cCrowdRender2D__cCrowdRender2D);
	void constructCrowdAnim2D(int param_1)
	{
		void* pvVar1;

		//pvVar1 = fun_00317d70(0x20, 0x4875d8, 0x20000000, 0);
		cCrowdAnim2D::cCrowdAnim2D(pvVar1, param_1);
		return;
	}

	INCLUDE_ASM("visualfx/crowdrender2d", cCrowdRender2D_init);
	void init()
	{

	}

	INCLUDE_ASM("visualfx/crowdrender2d", cCrowdRender2D_purge);

	INCLUDE_ASM("visualfx/crowdrender2d", cCrowdRender2D_constructCrowdAnim2D);
}


namespace cCrowdAnim2D
{
	INCLUDE_ASM("visualfx/crowdrender2d", cCrowdAnim2D_cCrowdAnim2D);
	void cCrowdAnim2D(void* pvVar1, int param_1)
	{

	}

	INCLUDE_ASM("visualfx/crowdrender2d", cCrowdAnim2D_advanceFrame);

	INCLUDE_ASM("visualfx/crowdrender2d", cCrowdAnim2D_update);
}
