#include "common.h"

struct cAnimSequence {
    char pad_0x00[0x98];
    float mCurrentWeight; // 0x98
    float mTargetWeight; // 0x9C
    float mFadeSpeed; // 0xA0
};

//100%
INCLUDE_ASM("animation/animsequencer", cAnimSequence_fadeWeight__FP13cAnimSequenceff);
#ifdef SKIP_ASM
void cAnimSequence_fadeWeight(cAnimSequence* self, float weight, float target)
{
    self->mCurrentWeight = weight;
    self->mTargetWeight = target;
    self->mFadeSpeed = 0.0f;
}
#endif

INCLUDE_ASM("animation/animsequencer", func_00313A20);

INCLUDE_ASM("animation/animsequencer", func_00313A70);

INCLUDE_ASM("animation/animsequencer", func_00313AD8);

INCLUDE_ASM("animation/animsequencer", func_00313BA8);

INCLUDE_ASM("animation/animsequencer", func_00313C08);

INCLUDE_ASM("animation/animsequencer", func_00313C50);

//100%
INCLUDE_ASM("animation/animsequencer", func_00313CF0);
#ifdef SKIP_ASM
extern "C" void func_00313CF0(void* self, int a1, float val)
{
    char* p = (char*)self + a1 * 0x1c;
    *(float*)(p + 0x8) = val;
    *(int*)((char*)self + 0xc4) = 1;
}
#endif

//100%
INCLUDE_ASM("animation/animsequencer", func_00313D28);
#ifdef SKIP_ASM
extern "C" void func_00313D28(void* self, int a1, float val)
{
    char* p = (char*)self + a1 * 0x1c;
    *(float*)(p + 0x14) = val;
}
#endif

//100%
INCLUDE_ASM("animation/animsequencer", func_00313D40);
#ifdef SKIP_ASM
extern "C" void func_00313D40(void* self, int a1, int val)
{
    char* p = (char*)self + a1 * 0x1c;
    *(int*)(p + 0x1c) = val;
}
#endif

INCLUDE_ASM("animation/animsequencer", func_00313D70);

INCLUDE_ASM("animation/animsequencer", func_00313DD0);

INCLUDE_ASM("animation/animsequencer", func_00314050);

//99.33%
INCLUDE_ASM("animation/animsequencer", func_003142E8__FPv);
#ifdef SKIP_ASM
void func_003142E8(void* self)
{
    int t0 = 0;
    *(int*)((char*)self + 0x4) = t0;
    *(int*)self = t0;
}
#endif

INCLUDE_ASM("animation/animsequencer", func_003142F8);

INCLUDE_ASM("animation/animsequencer", func_00314368);

INCLUDE_ASM("animation/animsequencer", func_00314418);

INCLUDE_ASM("animation/animsequencer", func_00314518);

INCLUDE_ASM("animation/animsequencer", func_00314588);

INCLUDE_ASM("animation/animsequencer", func_003145F8);

INCLUDE_ASM("animation/animsequencer", func_00314668);

INCLUDE_ASM("animation/animsequencer", func_003146D0);

INCLUDE_ASM("animation/animsequencer", func_00314718);

struct cAnimSequenceNode {
    char pad_0x00[0xC8];
    cAnimSequenceNode* next; // 0xC8
};

struct cAnimSequencer {
    char pad_0x00[0x4];
    cAnimSequenceNode* mFirstSequence; // 0x4
};

//100%
INCLUDE_ASM("animation/animsequencer", cAnimSequencer_getSequence__FP14cAnimSequenceri);
#ifdef SKIP_ASM
cAnimSequenceNode* cAnimSequencer_getSequence(cAnimSequencer* self, int index)
{
    cAnimSequenceNode* cur = self->mFirstSequence;
    while (cur != 0 && index-- > 0) {
        cur = cur->next;
    }
    return cur;
}
#endif

INCLUDE_ASM("animation/animsequencer", func_003147F0);

INCLUDE_ASM("animation/animsequencer", func_00314880);

//100%
INCLUDE_ASM("animation/animsequencer", func_00314978__FPv);
#ifdef SKIP_ASM
void* func_00314978(void* self)
{
    *(int*)self = 0;
    return self;
}
#endif

INCLUDE_ASM("animation/animsequencer", func_00314988);

INCLUDE_ASM("animation/animsequencer", func_003149D0);

extern "C" void* func_00314AA0(void*);

//75.56%
INCLUDE_ASM("animation/animsequencer", func_00314A18__FPvi);
#ifdef SKIP_ASM
void* func_00314A18(void* self, int a1)
{
    *(int*)self = a1;
    return func_00314AA0(self);
}
#endif

//100%
INCLUDE_ASM("animation/animsequencer", func_00314A40__FPv);
#ifdef SKIP_ASM
void* func_00314A40(void* self)
{
    *(int*)self = 0;
    return func_00314AA0(self);
}
#endif

INCLUDE_ASM("animation/animsequencer", func_00314AA0);

INCLUDE_ASM("animation/animsequencer", func_00314C00);

