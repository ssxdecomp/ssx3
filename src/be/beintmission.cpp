#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern const char D_0045A848[];
extern void* D_0045ADF8[16];
extern void* D_004A1238;

struct cBEMissionInterface {
    char pad_0x00[8];
    int field_0x8;
    void* vtable;
};

//99.58%
INCLUDE_ASM("be/beintmission", cBEMissionInterface_getThis__Fv);
#ifdef SKIP_ASM
void* cBEMissionInterface_getThis()
{
    if (D_004A1238 == 0) {
        cBEMissionInterface* mem = (cBEMissionInterface*)cMemMan_alloc(0x14, D_0045A848, 0, 0);
        mem->field_0x8 = 0;
        mem->vtable = D_0045ADF8;
        D_004A1238 = mem;
    }
    return D_004A1238;
}
#endif

INCLUDE_ASM("be/beintmission", func_00153350);

INCLUDE_ASM("be/beintmission", func_00153390);

INCLUDE_ASM("be/beintmission", func_00153498);

INCLUDE_ASM("be/beintmission", func_00153520);

INCLUDE_ASM("be/beintmission", cBEMissionInterface_getCurrentCollectForPeak);

INCLUDE_ASM("be/beintmission", func_00153688);

INCLUDE_ASM("be/beintmission", func_00153708);

INCLUDE_ASM("be/beintmission", func_001538E8);

INCLUDE_ASM("be/beintmission", func_00153B00);

INCLUDE_ASM("be/beintmission", func_00153C88);

INCLUDE_ASM("be/beintmission", func_00153D28);

INCLUDE_ASM("be/beintmission", func_00153D78);

INCLUDE_ASM("be/beintmission", func_00153DD0);

INCLUDE_ASM("be/beintmission", func_00153E28);

INCLUDE_ASM("be/beintmission", func_00153E80);

INCLUDE_ASM("be/beintmission", func_00153ED8);

INCLUDE_ASM("be/beintmission", func_00153FA0);

INCLUDE_ASM("be/beintmission", func_00153FD8);

INCLUDE_ASM("be/beintmission", func_00154010);

INCLUDE_ASM("be/beintmission", func_00154080);

INCLUDE_ASM("be/beintmission", func_001540F0);

INCLUDE_ASM("be/beintmission", func_00154160);

INCLUDE_ASM("be/beintmission", func_001541D0);

INCLUDE_ASM("be/beintmission", func_00154240);

INCLUDE_ASM("be/beintmission", func_00154278);

INCLUDE_ASM("be/beintmission", func_001542A0);

INCLUDE_ASM("be/beintmission", func_001542E0);

INCLUDE_ASM("be/beintmission", func_00154368);

INCLUDE_ASM("be/beintmission", func_001543E0);

INCLUDE_ASM("be/beintmission", func_001544D0);

INCLUDE_ASM("be/beintmission", func_00154588);

INCLUDE_ASM("be/beintmission", func_001545B0);

INCLUDE_ASM("be/beintmission", func_001545F8);

INCLUDE_ASM("be/beintmission", func_00154630);

INCLUDE_ASM("be/beintmission", func_00154678);

INCLUDE_ASM("be/beintmission", func_00154760);

INCLUDE_ASM("be/beintmission", func_001547A0);

//100%
INCLUDE_ASM("be/beintmission", func_001547D8__FPv);
#ifdef SKIP_ASM
void func_001547D8(void* self)
{
}
#endif

//100%
INCLUDE_ASM("be/beintmission", func_001547E0__FPv);
#ifdef SKIP_ASM
void func_001547E0(void* self)
{
}
#endif

INCLUDE_ASM("be/beintmission", func_001547E8);

INCLUDE_ASM("be/beintmission", func_00154898);

