#include "common.h"

INCLUDE_ASM("animation/animmodel", cAnimModel_addModelPartLOD);

//44.14%
INCLUDE_ASM("animation/animmodel", func_0030DB70__FPvi);
#ifdef SKIP_ASM
void* func_0030DB70(void* self, int a1)
{
    *(int*)((char*)((char*)self + *(int*)((char*)self + 0x60) * 4) + 0x64) = a1;
    *(int*)((char*)self + 0x60) = (int)(((char*)*(void**)((char*)self + 0x60) + 0x1));
    return ((char*)self + *(int*)((char*)self + 0x60) * 4);
}
#endif

//100%
INCLUDE_ASM("animation/animmodel", func_0030DB90);
#ifdef SKIP_ASM
extern "C" int func_0030DB90(void* self, void* a1)
{
    return *(int*)self - *(int*)a1;
}
#endif

INCLUDE_ASM("animation/animmodel", func_0030DBA0);

INCLUDE_ASM("animation/animmodel", cAnimModel_compile);

INCLUDE_ASM("animation/animmodel", func_0030E9E0);

INCLUDE_ASM("animation/animmodel", func_0030EA80);

INCLUDE_ASM("animation/animmodel", func_0030EB60);

INCLUDE_ASM("animation/animmodel", func_0030EBC0);

INCLUDE_ASM("animation/animmodel", func_0030EC18);

INCLUDE_ASM("animation/animmodel", func_0030ECA0);

INCLUDE_ASM("animation/animmodel", func_0030ECD8);

INCLUDE_ASM("animation/animmodel", func_0030F2B0);

INCLUDE_ASM("animation/animmodel", func_00310120);

INCLUDE_ASM("animation/animmodel", func_00310200);

INCLUDE_ASM("animation/animmodel", func_003103F0);

INCLUDE_ASM("animation/animmodel", func_00310530);

INCLUDE_ASM("animation/animmodel", func_00310640);

INCLUDE_ASM("animation/animmodel", func_00310948);

INCLUDE_ASM("animation/animmodel", func_00310C48);

INCLUDE_ASM("animation/animmodel", func_00310CE8);

INCLUDE_ASM("animation/animmodel", func_00310EA8);

INCLUDE_ASM("animation/animmodel", func_00310EE0);

INCLUDE_ASM("animation/animmodel", func_00310F18);

INCLUDE_ASM("animation/animmodel", func_00311048);

INCLUDE_ASM("animation/animmodel", func_003110D0);

INCLUDE_ASM("animation/animmodel", func_00311110);

INCLUDE_ASM("animation/animmodel", func_00311220);

INCLUDE_ASM("animation/animmodel", func_00311250);

INCLUDE_ASM("animation/animmodel", func_00311290);

INCLUDE_ASM("animation/animmodel", func_003112C8);

INCLUDE_ASM("animation/animmodel", func_00311318);

