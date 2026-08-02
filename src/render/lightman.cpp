#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern const char D_00492EE0[];
extern void* D_00493650[16];

struct cPSPLightMan;
cPSPLightMan* cPSPLightMan_cPSPLightMan(cPSPLightMan* self);

//100%
INCLUDE_ASM("render/lightman", cLightMan_construct__Fv);
#ifdef SKIP_ASM
void* cLightMan_construct()
{
    void* mem = cMemMan_alloc(0x14, D_00492EE0, 0, 0);
    cPSPLightMan_cPSPLightMan((cPSPLightMan*)mem);
    *(void**)mem = D_00493650;
    return mem;
}
#endif

//100%
INCLUDE_ASM("render/lightman", func_0038DC50__FPv);
#ifdef SKIP_ASM
void func_0038DC50(void* self)
{
}
#endif

//100%
INCLUDE_ASM("render/lightman", func_0038DC58__FPv);
#ifdef SKIP_ASM
void func_0038DC58(void* self)
{
}
#endif

//100%
INCLUDE_ASM("render/lightman", func_0038DC60__FPv);
#ifdef SKIP_ASM
void func_0038DC60(void* self)
{
}
#endif

//100%
INCLUDE_ASM("render/lightman", func_0038DC68__FPv);
#ifdef SKIP_ASM
void func_0038DC68(void* self)
{
}
#endif

INCLUDE_ASM("render/lightman", func_0038DC70);

INCLUDE_ASM("render/lightman", func_0038DEE8);

INCLUDE_ASM("render/lightman", func_0038DF38);

INCLUDE_ASM("render/lightman", func_0038DF98);

INCLUDE_ASM("render/lightman", func_0038E008);

INCLUDE_ASM("render/lightman", func_0038EC40);

INCLUDE_ASM("render/lightman", func_0038EE78);

INCLUDE_ASM("render/lightman", func_0038F2A8);

INCLUDE_ASM("render/lightman", func_0038F300);

INCLUDE_ASM("render/lightman", func_0038F460);

INCLUDE_ASM("render/lightman", func_0038F4F8);

INCLUDE_ASM("render/lightman", func_0038F598);

INCLUDE_ASM("render/lightman", func_0038F668);

INCLUDE_ASM("render/lightman", func_0038F6A8);

INCLUDE_ASM("render/lightman", func_0038F708);

INCLUDE_ASM("render/lightman", func_0038F738);

INCLUDE_ASM("render/lightman", func_0038F768);

INCLUDE_ASM("render/lightman", func_0038F7B0);

//100%
INCLUDE_ASM("render/lightman", func_0038F7F8__FPv);
#ifdef SKIP_ASM
void func_0038F7F8(void* self)
{
}
#endif

INCLUDE_ASM("render/lightman", func_0038F800);

INCLUDE_ASM("render/lightman", func_0038F930);

INCLUDE_ASM("render/lightman", func_0038FC48);

INCLUDE_ASM("render/lightman", func_00390198);

INCLUDE_ASM("render/lightman", func_00390458);

INCLUDE_ASM("render/lightman", func_003904A0);

INCLUDE_ASM("render/lightman", func_003905E8);

INCLUDE_ASM("render/lightman", func_00390C20);

INCLUDE_ASM("render/lightman", func_00390C60);

INCLUDE_ASM("render/lightman", func_00390EC8);

INCLUDE_ASM("render/lightman", func_00390EF8);

INCLUDE_ASM("render/lightman", func_00390F20);

INCLUDE_ASM("render/lightman", func_003912A8);

INCLUDE_ASM("render/lightman", func_00391360);

INCLUDE_ASM("render/lightman", func_00391418);

INCLUDE_ASM("render/lightman", func_00391480);

INCLUDE_ASM("render/lightman", func_003914F8);

INCLUDE_ASM("render/lightman", func_003915E8);

INCLUDE_ASM("render/lightman", func_003916C0);

INCLUDE_ASM("render/lightman", func_00391708);

