#include "common.h"

INCLUDE_ASM("wscript/wscriptcompile", cWScriptCompile_parseKeywords);

INCLUDE_ASM("wscript/wscriptcompile", func_00351120);

INCLUDE_ASM("wscript/wscriptcompile", func_00351170);

INCLUDE_ASM("wscript/wscriptcompile", func_003511D0);

//100%
INCLUDE_ASM("wscript/wscriptcompile", func_00351260__FPvT0);
#ifdef SKIP_ASM
int func_00351260(void* self, void* a1)
{
    int t0 = *(int*)((char*)self + 0x8);
    *(int*)a1 = t0;
    *(int*)((char*)self + 0x8) = (int)a1;
    return t0;
}
#endif

