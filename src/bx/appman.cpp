#include "common.h"

INCLUDE_ASM("bx/appman", cAppMan_cAppMan);

extern void* D_0048DBE8[16];
extern unsigned int D_004A5B64;
void operator_delete(int* ptr);

//99.92%
INCLUDE_ASM("bx/appman", cAppMan__cAppMan__FPvi);
#ifdef SKIP_ASM
void cAppMan__cAppMan(void* self, int flags)
{
    *(void**)((char*)self + 0x5C) = D_0048DBE8;
    D_004A5B64 = 0;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}
#endif

INCLUDE_ASM("bx/appman", cAppMan_run);

struct cAppMan {
    char pad_0x00[0x4];
    unsigned int mNextModule; // offset 0x4
    void* mExecutionMan; // offset 0x8
};

//100%
INCLUDE_ASM("bx/appman", cAppMan_setNextModule__FP7cAppManUi);
#ifdef SKIP_ASM
void cAppMan_setNextModule(cAppMan* self, unsigned int module)
{
    self->mNextModule = module;
}
#endif

INCLUDE_ASM("bx/appman", cAppMan_mainLoop);

int cExecutionMan_checkHalt(void* self, int flag);

//100%
INCLUDE_ASM("bx/appman", cAppMan_checkHalt__FP7cAppMan);
#ifdef SKIP_ASM
int cAppMan_checkHalt(cAppMan* self)
{
    return cExecutionMan_checkHalt(self->mExecutionMan, 1);
}
#endif

INCLUDE_ASM("bx/appman", func_00317348);

INCLUDE_ASM("bx/appman", cAppMan_loadexecpurge);

struct cExecutionMan {
    int field_0x0;
    int field_0x4;
    void* field_0x8;
};

extern void* D_0048DC30[16];

//100%
INCLUDE_ASM("bx/appman", cExecutionMan_halt__FP13cExecutionMan);
#ifdef SKIP_ASM
cExecutionMan* cExecutionMan_halt(cExecutionMan* self)
{
    self->field_0x0 = 0;
    self->field_0x8 = D_0048DC30;
    self->field_0x4 = 0;
    return self;
}
#endif

INCLUDE_ASM("bx/appman", cExecutionMan_checkHalt);

INCLUDE_ASM("bx/appman", func_00317500);

INCLUDE_ASM("bx/appman", func_00317520);

INCLUDE_ASM("bx/appman", func_00317530);

INCLUDE_ASM("bx/appman", func_00317550);

INCLUDE_ASM("bx/appman", func_003175A0);

INCLUDE_ASM("bx/appman", func_00317600);

