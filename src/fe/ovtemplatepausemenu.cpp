#include "common.h"

INCLUDE_ASM("fe/ovtemplatepausemenu", cOVTemplate_PauseMenu_onCreateScreen);

INCLUDE_ASM("fe/ovtemplatepausemenu", func_001F8448);

INCLUDE_ASM("fe/ovtemplatepausemenu", func_001F85C0);

//100%
INCLUDE_ASM("fe/ovtemplatepausemenu", func_001F8720__FPv);
#ifdef SKIP_ASM
void func_001F8720(void* self)
{
}
#endif

INCLUDE_ASM("fe/ovtemplatepausemenu", func_001F8728);

extern "C" void* func_0020A430(void*);

//100%
INCLUDE_ASM("fe/ovtemplatepausemenu", func_001F88E8__FPv);
#ifdef SKIP_ASM
void* func_001F88E8(void* self)
{
    *(int*)((char*)self + 0xc4) = 0;
    return func_0020A430(self);
}
#endif

INCLUDE_ASM("fe/ovtemplatepausemenu", func_001F8908);

INCLUDE_ASM("fe/ovtemplatepausemenu", cOVTemplate_PauseMenu_onWidgetEvent);

//100%
INCLUDE_ASM("fe/ovtemplatepausemenu", func_001F8DF0__FPv);
#ifdef SKIP_ASM
int func_001F8DF0(void* self)
{
    return 0;
}
#endif

INCLUDE_ASM("fe/ovtemplatepausemenu", func_001F8DF8);

INCLUDE_ASM("fe/ovtemplatepausemenu", func_001F8EE0);

INCLUDE_ASM("fe/ovtemplatepausemenu", func_001F8F48);

INCLUDE_ASM("fe/ovtemplatepausemenu", func_001F8FB0);

INCLUDE_ASM("fe/ovtemplatepausemenu", func_001F9018);

INCLUDE_ASM("fe/ovtemplatepausemenu", func_001F9080);

INCLUDE_ASM("fe/ovtemplatepausemenu", func_001F90E8);

