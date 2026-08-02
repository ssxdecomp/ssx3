#include "common.h"

INCLUDE_ASM("fe/uitemplatemap", cUITemplate_MAP_onCreateScreen);

INCLUDE_ASM("fe/uitemplatemap", func_002009D0);

INCLUDE_ASM("fe/uitemplatemap", func_00200A70);

INCLUDE_ASM("fe/uitemplatemap", func_00200AC0);

INCLUDE_ASM("fe/uitemplatemap", func_00200AF0);

INCLUDE_ASM("fe/uitemplatemap", func_00200B50);

INCLUDE_ASM("fe/uitemplatemap", func_00200D00);

INCLUDE_ASM("fe/uitemplatemap", cUITemplate_MAP_setupMenus);

struct cUITemplate_MAP {
    char pad_0x00[0x10];
    int field_0x10;
    int field_0x14;
    int field_0x18;
    int field_0x1C;
};
extern unsigned int D_004A2594;

//99.9%
INCLUDE_ASM("fe/uitemplatemap", cUITemplate_MAP_setupEventUnlock__FP15cUITemplate_MAP);
#ifdef SKIP_ASM
void cUITemplate_MAP_setupEventUnlock(cUITemplate_MAP* self)
{
    self->field_0x1C = 0;
    self->field_0x10 = 1;
    self->field_0x14 = 1;
    if (D_004A2594 < 2) {
        self->field_0x18 = 0;
    } else {
        self->field_0x18 = 1;
    }
}
#endif

INCLUDE_ASM("fe/uitemplatemap", cUITemplate_MAP_setupPeakUnlock);

INCLUDE_ASM("fe/uitemplatemap", func_00201868);

INCLUDE_ASM("fe/uitemplatemap", func_002018A8);

INCLUDE_ASM("fe/uitemplatemap", func_00202738);

//100%
INCLUDE_ASM("fe/uitemplatemap", func_00202768__FPv);
#ifdef SKIP_ASM
int func_00202768(void* self)
{
    return 0;
}
#endif

INCLUDE_ASM("fe/uitemplatemap", func_00202770);

INCLUDE_ASM("fe/uitemplatemap", cUITemplate_MAP_onUpdate);

INCLUDE_ASM("fe/uitemplatemap", cUITemplate_MAP_setupLayout);

INCLUDE_ASM("fe/uitemplatemap", cUITemplate_MAP_setupMenuFocus);

INCLUDE_ASM("fe/uitemplatemap", cUITemplate_MAP_setupMapPic);

INCLUDE_ASM("fe/uitemplatemap", cUITemplate_MAP_setupPopup);

INCLUDE_ASM("fe/uitemplatemap", cUITemplate_MAP_setShowInfo);

INCLUDE_ASM("fe/uitemplatemap", cUITemplate_MAP_setupPeakInfo);

INCLUDE_ASM("fe/uitemplatemap", func_00204FF0);

INCLUDE_ASM("fe/uitemplatemap", cUITemplate_MAP_setupPeakGoals);

INCLUDE_ASM("fe/uitemplatemap", cUITemplate_MAP_showEventPath);

INCLUDE_ASM("fe/uitemplatemap", func_00207430);

INCLUDE_ASM("fe/uitemplatemap", func_002083D8);

INCLUDE_ASM("fe/uitemplatemap", func_00208438);

INCLUDE_ASM("fe/uitemplatemap", func_00208498);

INCLUDE_ASM("fe/uitemplatemap", func_00208518);

INCLUDE_ASM("fe/uitemplatemap", func_00208538);

INCLUDE_ASM("fe/uitemplatemap", func_00208558);

INCLUDE_ASM("fe/uitemplatemap", func_00208588);

INCLUDE_ASM("fe/uitemplatemap", func_002085B8);

INCLUDE_ASM("fe/uitemplatemap", func_00208610);

INCLUDE_ASM("fe/uitemplatemap", func_00208638);

INCLUDE_ASM("fe/uitemplatemap", func_00208658);

INCLUDE_ASM("fe/uitemplatemap", func_00208678);

