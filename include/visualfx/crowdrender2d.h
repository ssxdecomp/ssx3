#ifndef CROWDRENDER2D_H
#define CROWDRENDER2D_H

#include "common.h"
int cCrowdRender2D_cCrowdRender2D(int param_1);
void* cCrowdRender2D_constructCrowdAnim2D(void* param);
void cCrowdRender2D_init();
void* cCrowdAnim2D_cCrowdAnim2D(void* memory, void* param_1);
int cCrowdRender2D_purge(int* param_1);
void operator_delete(int* param_1);

extern const char D_004875D8[];

#endif /* CROWDRENDER2D_H */