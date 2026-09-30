#include "common.h"

INCLUDE_ASM("ai/ridermetrix", cRiderMetrix_linkToRider);

INCLUDE_ASM("ai/ridermetrix", func_001173B8);

INCLUDE_ASM("ai/ridermetrix", func_00117400);

INCLUDE_ASM("ai/ridermetrix", func_001174B0);

INCLUDE_ASM("ai/ridermetrix", func_001174E8);

//100%
INCLUDE_ASM("ai/ridermetrix", func_00117520);
#ifdef SKIP_ASM
extern "C" void func_00117520(void* self, int a1)
{
    int delta = a1 - *(int*)((char*)self + 0x1c8);
    *(int*)((char*)self + 0x1c8) = a1;
    *(int*)((char*)self + 0x198) += delta;
}
#endif

INCLUDE_ASM("ai/ridermetrix", func_00117540);

INCLUDE_ASM("ai/ridermetrix", func_001175B8);

INCLUDE_ASM("ai/ridermetrix", func_001175F8);

INCLUDE_ASM("ai/ridermetrix", func_00117638);

//100%
INCLUDE_ASM("ai/ridermetrix", func_001176F8);
#ifdef SKIP_ASM
extern "C" void func_001176F8(void* self)
{
    *(float*)((char*)self + 0xa4) = -1.0f;
}
#endif

INCLUDE_ASM("ai/ridermetrix", func_00117708);

INCLUDE_ASM("ai/ridermetrix", func_00117718);

INCLUDE_ASM("ai/ridermetrix", func_00117838);

//100%
INCLUDE_ASM("ai/ridermetrix", func_00117900__FPv);
#ifdef SKIP_ASM
float func_00117900(void* self)
{
    return *(float*)((char*)self + 0x14);
}
#endif

INCLUDE_ASM("ai/ridermetrix", func_00117908);

INCLUDE_ASM("ai/ridermetrix", func_00117948);

INCLUDE_ASM("ai/ridermetrix", func_00117990);

INCLUDE_ASM("ai/ridermetrix", func_001179E0);

INCLUDE_ASM("ai/ridermetrix", func_00117A58);

INCLUDE_ASM("ai/ridermetrix", func_00117AE8);

INCLUDE_ASM("ai/ridermetrix", func_00117B88);

INCLUDE_ASM("ai/ridermetrix", func_00117C28);

INCLUDE_ASM("ai/ridermetrix", func_00117FE0);

INCLUDE_ASM("ai/ridermetrix", func_00118FF8);

INCLUDE_ASM("ai/ridermetrix", func_00119068);

INCLUDE_ASM("ai/ridermetrix", func_001190F0);

INCLUDE_ASM("ai/ridermetrix", func_00119210);

INCLUDE_ASM("ai/ridermetrix", func_00119310);

INCLUDE_ASM("ai/ridermetrix", func_00119368);

extern "C" void func_00117718(void*);

//99.38% - identical instructions; jal addend differs only because the
// callee sits at a different .text offset in our object than in the target
INCLUDE_ASM("ai/ridermetrix", func_001193E0);
#ifdef SKIP_ASM
extern "C" float func_001193E0(void* self)
{
    func_00117718(self);
    return 0.0f;
}
#endif

INCLUDE_ASM("ai/ridermetrix", func_00119400);

INCLUDE_ASM("ai/ridermetrix", func_00119448);

INCLUDE_ASM("ai/ridermetrix", func_001194C0);

INCLUDE_ASM("ai/ridermetrix", func_001195A8);

INCLUDE_ASM("ai/ridermetrix", func_001195D8);

INCLUDE_ASM("ai/ridermetrix", func_00119608);

INCLUDE_ASM("ai/ridermetrix", func_00119708);

INCLUDE_ASM("ai/ridermetrix", func_001197D8);

INCLUDE_ASM("ai/ridermetrix", func_00119898);

INCLUDE_ASM("ai/ridermetrix", func_001198D8);

extern "C" void* func_00119898(void*);

//99.29%
INCLUDE_ASM("ai/ridermetrix", func_00119918__FPvi);
#ifdef SKIP_ASM
void* func_00119918(void* self, int a1)
{
    *(int*)((char*)self + 0x20) = a1;
    return func_00119898(self);
}
#endif

//97.62%
INCLUDE_ASM("ai/ridermetrix", func_00119938__FPvii);
#ifdef SKIP_ASM
float func_00119938(void* self, int a1, int a2)
{
    *(int*)((char*)self + 0x6c) = 0;
    *(int*)((char*)self + 0x20) = a2;
    *(int*)((char*)self + 0x70) = a1;
    *(int*)((char*)self + 0x5c) = 1;
    *(int*)((char*)self + 0xc) = a2;
    return *(float*)((char*)self + 0x6c);
}
#endif

INCLUDE_ASM("ai/ridermetrix", func_00119958);

INCLUDE_ASM("ai/ridermetrix", func_001199F8);

INCLUDE_ASM("ai/ridermetrix", func_00119A38);

INCLUDE_ASM("ai/ridermetrix", func_00119AD8);

INCLUDE_ASM("ai/ridermetrix", func_00119B08);

INCLUDE_ASM("ai/ridermetrix", func_00119BB0);

INCLUDE_ASM("ai/ridermetrix", func_00119BF0);

INCLUDE_ASM("ai/ridermetrix", func_00119C38);

INCLUDE_ASM("ai/ridermetrix", func_00119C98);

INCLUDE_ASM("ai/ridermetrix", func_00119D40);

INCLUDE_ASM("ai/ridermetrix", func_00119E38);

INCLUDE_ASM("ai/ridermetrix", func_00119EF8);

extern "C" void func_00117AE8(void* self, int a, const char* b, float c, int d);
extern const char D_00457888[];

//100%
INCLUDE_ASM("ai/ridermetrix", cRiderMetrix_evAutoResetSurface__FPv);
#ifdef SKIP_ASM
float cRiderMetrix_evAutoResetSurface(void* self)
{
    func_00117AE8(self, 0x33, D_00457888, 1.5f, 0);
    return 0.0f;
}
#endif

//100%
INCLUDE_ASM("ai/ridermetrix", func_0011A0C0__FPv);
#ifdef SKIP_ASM
float func_0011A0C0(void* self)
{
    return 0.0f;
}
#endif

INCLUDE_ASM("ai/ridermetrix", func_0011A0E0);

INCLUDE_ASM("ai/ridermetrix", func_0011A110);

INCLUDE_ASM("ai/ridermetrix", func_0011A168);

// 8-byte packed trick identity built by func_0011A8C8
struct sTrickId {
    int w0;
    int w1;
};

struct sGameSettings {
    char pad_0x00[0x48];
    signed char eventKind; // 0x48: 4 = free ride
    signed char gameType;  // 0x49: 0 = Conquer the Mountain
};

struct sScoreGrades {
    char pad_0x00[0x16c];
    int gradeCounts[6]; // 0x16c: landed tricks per grade (func_00119310)
};

extern void* D_004A28A8;
extern sGameSettings D_00535BC8;

extern "C" void func_001179E0(void* self, int type);
extern "C" int func_0012A250(void* race);
extern "C" int func_0011A8C8(void* self, sTrickId* id, int stance, int alternate, int style, int flag);
extern "C" int func_00117948(void* self);
extern "C" int func_0011B1A8(void* self, sTrickId* id);
extern "C" void func_00117B88(void* self, int type, int value, int arg, float duration);
extern "C" void* func_0028B180();
extern "C" void func_0029B7E0(void* audio, int rider);
extern "C" int func_001190F0(void* self, sTrickId* id);
extern "C" void func_00118FF8(void* self, sTrickId* id, int repeat);
extern "C" int func_00117990(void* self);
extern "C" int func_00119310(void* self, int points);
extern "C" int func_00117908(void* self);
extern "C" void func_00117638(void* self, int points);
extern "C" void func_0029B430(void* audio, int rider, int ubers, int runUbers);
extern "C" void func_00119EF8(void* self, int kind, int amount);
extern "C" void func_00117708(void* self, float seconds);
extern "C" void* cBE_getBE();
void* cBE_getInterface(void* be, int kind);
extern "C" int abs(int);

// g++ max operator: the target uses max.s, which only `>?` produces
#define MAX(a, b) ((a) >? (b))

// Rounds whole degrees to the nearest multiple of 180.
static inline int func_roundDegrees(int deg)
{
    int r = deg % 180;
    if (r < -90) {
        return deg - r - 180;
    }
    if (r > 90) {
        return deg - r + 180;
    }
    return deg - r;
}

// Trick landing commit: names and scores the trick that just ended, updates
// the run statistics and the combo, and returns the meter delta.
//100%
INCLUDE_ASM("ai/ridermetrix", func_0011A228);
#ifdef SKIP_ASM
extern "C" float func_0011A228(void* self, int stance, int alternate, int style, int flag, int takeoff)
{
    sTrickId id;
    float delta;
    int valid;
    int repeats;
    int divisor;
    int pending;
    int grade;
    int inverted;
    int points;
    int total;
    int spin;
    int flip;
    int career;

    func_001179E0(self, 1);
    func_001179E0(self, 2);
    func_001179E0(self, 4);
    func_001179E0(self, 0x1c);
    func_001179E0(self, 0x1d);
    func_001179E0(self, 0x1e);
    func_001179E0(self, 0x1f);
    func_001179E0(self, 0x20);

    if (func_0012A250(*(void**)(*(char**)((char*)D_004A28A8 + 0x84) + 0xc))) {
        return 0.0f;
    }

    valid = func_0011A8C8(self, &id, stance, alternate, style, flag);
    delta = 0.0f;
    if (func_00117948(self) > 0) {
        repeats = 0;
        if (valid) {
            int bonus = func_0011B1A8(self, &id);
            if (bonus > 0) {
                *(float*)((char*)self + 0x14) += (float)bonus * 0.0001f;
                func_00117B88(self, 0x32, bonus, 0, 1.5f);
                func_0029B7E0(func_0028B180(), *(int*)((char*)self + 0x1ac));
            }
            repeats = func_001190F0(self, &id);
            func_00118FF8(self, &id, repeats > 0);
        }
        divisor = repeats + 1;
        pending = func_00117948(self);
        points = func_00117990(self);
        grade = func_00119310(self, pending);
        inverted = func_00117908(self);
        func_00117638(self, pending / divisor);
        delta = func_00117900(self) / (float)divisor;

        points /= divisor;
        points -= points % 10;
        *(int*)((char*)self + 0x198) += points + inverted;
        *(int*)((char*)self + 0x19c) += inverted;
        *(int*)((char*)self + 0x110) += 1;
        ((sScoreGrades*)self)->gradeCounts[grade]++;

        if (*(int*)((char*)self + 0x18c) < pending) {
            *(int*)((char*)self + 0x18c) = pending;
            *(sTrickId*)((char*)self + 0x190) = id;
        }

        spin = func_roundDegrees((int)(*(float*)((char*)self + 0x34) * 57.29578f));
        flip = func_roundDegrees((int)(*(float*)((char*)self + 0x38) * 57.29578f));
        *(int*)((char*)self + 0xfc) += abs(spin);
        *(int*)((char*)self + 0x100) += abs(flip);
        *(float*)((char*)self + 0x144) += *(float*)((char*)self + 0x44);
        *(int*)((char*)self + 0x104) += *(int*)((char*)self + 0x4c);
        *(int*)((char*)self + 0x108) += *(int*)((char*)self + 0x80);

        if (*(int*)((char*)self + 0x54) > 0) {
            func_0029B430(func_0028B180(), *(int*)((char*)self + 0x1ac), *(int*)((char*)self + 0x54),
                          *(int*)((char*)self + 0x114));
        }

        *(int*)((char*)self + 0x114) += *(int*)((char*)self + 0x54);
        *(int*)((char*)self + 0x118) += *(int*)((char*)self + 0x58);
        *(int*)((char*)self + 0x11c) += *(int*)((char*)self + 0x74);
        *(float*)((char*)self + 0x14c) = MAX(*(float*)((char*)self + 0x30), *(float*)((char*)self + 0x14c));
        *(float*)((char*)self + 0x150) = MAX(*(float*)((char*)self + 0x48), *(float*)((char*)self + 0x150));
        *(float*)((char*)self + 0x154) = MAX(*(float*)((char*)self + 0x24), *(float*)((char*)self + 0x154));
        *(float*)((char*)self + 0x158) = MAX(*(float*)((char*)self + 0x78), *(float*)((char*)self + 0x158));
        *(int*)((char*)self + 0x198) += *(int*)((char*)self + 0x84);
        total = points + *(int*)((char*)self + 0x84) + inverted;

        cBE_getInterface(cBE_getBE(), 0);
        // free ride in Conquer the Mountain pays the career instead of the HUD
        career = D_00535BC8.eventKind == 4 && D_00535BC8.gameType == 0;
        if (!career) {
            if (repeats > 0) {
                func_00117B88(self, 0x24, total, grade, 2.5f);
            } else {
                func_00117B88(self, 0x23, total, grade, 2.5f);
            }
            func_00117B88(self, 0x18, total, 0, 0.7f);
        } else {
            int amount = total / 500;
            if (amount > 20) {
                amount = 20;
            }
            func_00119EF8(self, 0, amount);
        }
    }

    if (!takeoff) {
        if (style != 0 || flag != 0) {
            return delta;
        }
    } else if (*(int*)((char*)self + 0x20) != 0 || *(int*)((char*)self + 0x28) != 0) {
        return delta;
    }
    if (*(float*)((char*)self + 0x14) > 0.0f || *(float*)((char*)self + 0xa4) < 0.0f) {
        func_00117708(self, 1.5f);
    }
    return delta;
}
#endif

INCLUDE_ASM("ai/ridermetrix", func_0011A7A8);

INCLUDE_ASM("ai/ridermetrix", func_0011A8C8);

INCLUDE_ASM("ai/ridermetrix", func_0011B1A8);

INCLUDE_ASM("ai/ridermetrix", func_0011B2C0);

INCLUDE_ASM("ai/ridermetrix", func_0011B3F8);

extern "C" void* func_0041AA88(void* self);

//100%
INCLUDE_ASM("ai/ridermetrix", func_0011B678__FPv);
#ifdef SKIP_ASM
void* func_0011B678(void* self)
{
    return func_0041AA88(self);
}
#endif

