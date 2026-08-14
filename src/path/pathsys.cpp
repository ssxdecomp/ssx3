#include "common.h"

INCLUDE_ASM("path/pathsys", cPathSys_resolvePaths);

INCLUDE_ASM("path/pathsys", func_0026B410);

INCLUDE_ASM("path/pathsys", func_0026B508);

INCLUDE_ASM("path/pathsys", func_0026B550);

INCLUDE_ASM("path/pathsys", func_0026B598);

INCLUDE_ASM("path/pathsys", func_0026B5E0);

INCLUDE_ASM("path/pathsys", func_0026B680);

INCLUDE_ASM("path/pathsys", func_0026B7D8);

INCLUDE_ASM("path/pathsys", func_0026B880);

extern "C" void* func_003E6574(void*, void*, int);

//100%
INCLUDE_ASM("path/pathsys", func_0026BA48);
#ifdef SKIP_ASM
extern "C" void func_0026BA48(void* dst, void* src)
{
    if (dst != src) {
        func_003E6574(dst, src, 0xc);
    }
}
#endif

//100%
INCLUDE_ASM("path/pathsys", func_0026BA68);
#ifdef SKIP_ASM
extern "C" void func_0026BA68(void* dst, void* src)
{
    if (dst != src) {
        func_003E6574(dst, src, 0x4);
    }
}
#endif

//100%
INCLUDE_ASM("path/pathsys", func_0026BA88);
#ifdef SKIP_ASM
extern "C" void func_0026BA88(void* dst, void* src)
{
    if (dst != src) {
        func_003E6574(dst, src, 0x4);
    }
}
#endif

INCLUDE_ASM("path/pathsys", func_0026BAE8);

//100%
INCLUDE_ASM("path/pathsys", func_0026C410__FPv);
#ifdef SKIP_ASM
void func_0026C410(void* self)
{
}
#endif

//100%
INCLUDE_ASM("path/pathsys", func_0026C418__FPv);
#ifdef SKIP_ASM
void func_0026C418(void* self)
{
}
#endif

extern "C" void* func_0026BAE8(int, int);

//99.38%
INCLUDE_ASM("path/pathsys", func_0026C438__FPv);
#ifdef SKIP_ASM
void* func_0026C438(void* self)
{
    return func_0026BAE8(1, 0xffff);
}
#endif

