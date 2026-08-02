#include "common.h"

INCLUDE_ASM("bx/appman", cAppMan_cAppMan);

extern void* D_0048DBE8[16];
extern void* D_004A5B64;
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

//93.78%
INCLUDE_ASM("bx/appman", func_00317348__FPv);
#ifdef SKIP_ASM
int func_00317348(void* self)
{
    float f28 = *(float*)((char*)self + 0x28);
    float f24 = *(float*)((char*)self + 0x24);
    int i28 = (int)f28;
    int cnt = *(int*)((char*)self + 0x18);
    float sum = f28 + f24;
    cnt = cnt + 1;
    *(int*)((char*)self + 0x18) = cnt;
    int isum = (int)sum;
    int n = isum - i28;
    float fn = (float)n;
    n = n - 1;
    sum = sum - fn;
    *(float*)((char*)self + 0x28) = sum;

    if (n != -1) {
        void* obj = *(void**)((char*)self + 0x5C);
        do {
            n--;
            short off = *(short*)((char*)obj + 0x38);
            void (*fn2)(void*) = *(void (**)(void*))((char*)obj + 0x3C);
            fn2((char*)self + off);
            obj = *(void**)((char*)self + 0x5C);
        } while (n != -1);
    }

    void* obj2 = *(void**)((char*)self + 0x8);
    void* inner = *(void**)((char*)obj2 + 0x8);
    short off2 = *(short*)((char*)inner + 0x28);
    void (*fn3)(void*) = *(void (**)(void*))((char*)inner + 0x2C);
    fn3((char*)obj2 + off2);
}
#endif

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

//100%
INCLUDE_ASM("bx/appman", cExecutionMan_checkHalt__FPvi);
#ifdef SKIP_ASM
int cExecutionMan_checkHalt(void* self, int flag)
{
    void (*fn)(void*) = *(void (**)(void*))self;
    if (fn != 0) {
        fn(*(void**)((char*)self + 0x4));
        if (flag != 0) {
            void* vt = *(void**)((char*)self + 0x8);
            short off = *(short*)((char*)vt + 0x70);
            void (*fn2)(void*) = *(void (**)(void*))((char*)vt + 0x74);
            fn2((char*)self + off);
        }
    }
}
#endif

//99.25%
INCLUDE_ASM("bx/appman", func_00317500__Fv);
#ifdef SKIP_ASM
int func_00317500(void)
{
    return func_00317348(D_004A5B64);
}
#endif

//99.67%
INCLUDE_ASM("bx/appman", func_00317520__Fv);
#ifdef SKIP_ASM
int func_00317520(void)
{
    return *(int*)((char*)D_004A5B64 + 0x8);
}
#endif

//99.29%
INCLUDE_ASM("bx/appman", func_00317530__FPvf);
#ifdef SKIP_ASM
void func_00317530(void* self, float arg)
{
    *(float*)((char*)self + 0xC) = arg;
    *(int*)((char*)self + 0x1C) = 0;
    *(int*)((char*)self + 0x0) = 0;
    *(int*)((char*)self + 0x8) = 0;
    *(int*)((char*)self + 0x14) = 0;
    *(int*)((char*)self + 0x18) = 0;
}
#endif

extern float D_004A01FC;

//99.9%
INCLUDE_ASM("bx/appman", func_00317550__FPvf);
#ifdef SKIP_ASM
void func_00317550(void* self, float arg)
{
    float old8 = *(float*)((char*)self + 0x8);
    float raw = *(float*)((char*)self + 0xC);
    float diff = arg - old8;
    float x0 = *(float*)((char*)self + 0x0);
    float rate = raw * diff;
    int v1 = *(int*)((char*)D_004A5B64 + 0x1C);
    x0 = x0 - arg;
    rate = rate * D_004A01FC;
    *(float*)((char*)self + 0x4) = old8;
    *(float*)((char*)self + 0x18) = x0;
    *(int*)((char*)self + 0x10) = v1;
    float result = -1.5f / rate;
    *(float*)((char*)self + 0x14) = arg;
    *(float*)((char*)self + 0x8) = arg;
    *(float*)((char*)self + 0x1C) = result;
}
#endif

extern "C" float func_0040D758(float);

//99.96%
INCLUDE_ASM("bx/appman", func_003175A0__FPv);
#ifdef SKIP_ASM
void func_003175A0(void* self)
{
    int delta = *(int*)((char*)D_004A5B64 + 0x1C) - *(int*)((char*)self + 0x10);
    float ret = func_0040D758((float)delta * *(float*)((char*)D_004A5B64 + 0x14) * *(float*)((char*)self + 0x1C));
    *(float*)((char*)self + 0x0) = *(float*)((char*)self + 0x14) + *(float*)((char*)self + 0x18) * ret;
}
#endif

//99.67%
INCLUDE_ASM("bx/appman", func_00317600__FPv);
#ifdef SKIP_ASM
void func_00317600(void* self)
{
    *(int*)((char*)self + 0x18) = 0;
    *(float*)((char*)self + 0x0) = 100.0f;
    *(float*)((char*)self + 0x14) = 100.0f;
}
#endif

