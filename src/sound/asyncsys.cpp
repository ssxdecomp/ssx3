#include "common.h"

void* operator_new(unsigned int size);

struct cAsyncSys {
    char pad_0x00[0x1CC];
    void* field_0x1CC;
    int field_0x1D0;
};

//63.76% - target has a dead address computation (D_00482988) not reproduced; logic correct
INCLUDE_ASM("sound/asyncsys", cAsyncSys_ASYNCSYS_Init__FP9cAsyncSysUi);
#ifdef SKIP_ASM
void cAsyncSys_ASYNCSYS_Init(cAsyncSys* self, unsigned int x)
{
    if (x != 0) {
        self->field_0x1D0 = x;
        self->field_0x1CC = operator_new(x);
    }
}
#endif

INCLUDE_ASM("sound/asyncsys", func_0028A230);

INCLUDE_ASM("sound/asyncsys", func_0028A298);

INCLUDE_ASM("sound/asyncsys", func_0028A558);

INCLUDE_ASM("sound/asyncsys", func_0028A728);

INCLUDE_ASM("sound/asyncsys", func_0028AAF8);

INCLUDE_ASM("sound/asyncsys", func_0028B180);

INCLUDE_ASM("sound/asyncsys", func_0028B1B0);

INCLUDE_ASM("sound/asyncsys", func_0028B1C0);

INCLUDE_ASM("sound/asyncsys", func_0028B1C8);

INCLUDE_ASM("sound/asyncsys", func_0028B1D8);

INCLUDE_ASM("sound/asyncsys", func_0028B1E8);

INCLUDE_ASM("sound/asyncsys", func_0028B1F8);

INCLUDE_ASM("sound/asyncsys", func_0028B210);

//100%
INCLUDE_ASM("sound/asyncsys", func_0028B240__FPv);
#ifdef SKIP_ASM
int func_0028B240(void* self)
{
    return 0x3C;
}
#endif

INCLUDE_ASM("sound/asyncsys", func_0028B248);

INCLUDE_ASM("sound/asyncsys", func_0028B278);

INCLUDE_ASM("sound/asyncsys", func_0028B2D0);

INCLUDE_ASM("sound/asyncsys", func_0028B320);

INCLUDE_ASM("sound/asyncsys", func_0028B528);

