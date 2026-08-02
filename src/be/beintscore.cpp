#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void func_001549A8(void* self);
extern const char D_0045A858[];
extern void* D_004A1248;

struct cBEScoreInterface {
    char pad_0x00[8];
    int field_0x8;
    char pad_0xC[4];
    int field_0x10;
    int field_0x14;
    int field_0x18;
    int field_0x1C;
};

//86.17% - post-call register/global-reload scheduling not fully reproduced
INCLUDE_ASM("be/beintscore", cBEScoreInterface_getThis__Fv);
#ifdef SKIP_ASM
void* cBEScoreInterface_getThis()
{
    if (D_004A1248 == 0) {
        cBEScoreInterface* mem = (cBEScoreInterface*)cMemMan_alloc(0x230, D_0045A858, 0, 0);
        D_004A1248 = mem;
        func_001549A8(mem);
        cBEScoreInterface* mem2 = (cBEScoreInterface*)D_004A1248;
        mem2->field_0x1C = -1;
        mem2->field_0x8 = 0;
        mem2->field_0x10 = 0;
        mem2->field_0x14 = 0;
        mem2->field_0x18 = -1;
    }
    return D_004A1248;
}
#endif

INCLUDE_ASM("be/beintscore", func_001549A8);

//100%
INCLUDE_ASM("be/beintscore", func_001549E0__FPv);
#ifdef SKIP_ASM
void func_001549E0(void* self)
{
}
#endif

INCLUDE_ASM("be/beintscore", func_001549E8);

INCLUDE_ASM("be/beintscore", func_00154A58);

INCLUDE_ASM("be/beintscore", func_00154AB8);

INCLUDE_ASM("be/beintscore", func_00154EE8);

INCLUDE_ASM("be/beintscore", func_001550E8);

INCLUDE_ASM("be/beintscore", func_00155130);

INCLUDE_ASM("be/beintscore", func_00155190);

INCLUDE_ASM("be/beintscore", func_00155208);

INCLUDE_ASM("be/beintscore", func_00155270);

INCLUDE_ASM("be/beintscore", func_00155288);

signed char cBELibrary_getCharacterID(int index);
extern char D_004A6CA8[];

//97.94%
INCLUDE_ASM("be/beintscore", cBEScoreInterface_getCurrentHighlightLevel__FPvi);
#ifdef SKIP_ASM
signed char cBEScoreInterface_getCurrentHighlightLevel(void* self, int riderIndex)
{
    int charID = cBELibrary_getCharacterID(0);
    char* p = D_004A6CA8 + riderIndex + charID * 0xF88;
    return p[0xBB8];
}
#endif

INCLUDE_ASM("be/beintscore", func_00155328);

//100%
INCLUDE_ASM("be/beintscore", func_00155380__FPv);
#ifdef SKIP_ASM
void func_00155380(void* self)
{
}
#endif

//100%
INCLUDE_ASM("be/beintscore", func_00155388__FPv);
#ifdef SKIP_ASM
void func_00155388(void* self)
{
}
#endif

INCLUDE_ASM("be/beintscore", func_00155390);

INCLUDE_ASM("be/beintscore", func_00155420);

INCLUDE_ASM("be/beintscore", func_001557E0);

INCLUDE_ASM("be/beintscore", func_001558F8);

