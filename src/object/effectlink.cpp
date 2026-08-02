#include "common.h"

struct cEffectLink {
    cEffectLink* next; // 0x0
    cEffectLink* prev; // 0x4
};

//100%
INCLUDE_ASM("object/effectlink", cEffectLink_add__FP11cEffectLinkT0);
#ifdef SKIP_ASM
void cEffectLink_add(cEffectLink* link, cEffectLink* other)
{
    if (link->next != 0) {
        link->next->prev = other;
    }
    other->prev = link;
    other->next = link->next;
    link->next = other;
}
#endif

INCLUDE_ASM("object/effectlink", func_00345720);

INCLUDE_ASM("object/effectlink", func_00345760);

INCLUDE_ASM("object/effectlink", func_00345798);

INCLUDE_ASM("object/effectlink", func_003457C8);

INCLUDE_ASM("object/effectlink", func_00345828);

INCLUDE_ASM("object/effectlink", func_00345890);

INCLUDE_ASM("object/effectlink", func_003458C0);

INCLUDE_ASM("object/effectlink", func_003459A8);

INCLUDE_ASM("object/effectlink", func_00345AD0);

INCLUDE_ASM("object/effectlink", func_00345B40);

INCLUDE_ASM("object/effectlink", func_00345BC8);

INCLUDE_ASM("object/effectlink", func_00345BF0);

INCLUDE_ASM("object/effectlink", func_00345C90);

INCLUDE_ASM("object/effectlink", func_00345D80);

INCLUDE_ASM("object/effectlink", func_00345E88);

INCLUDE_ASM("object/effectlink", func_00345EF8);

INCLUDE_ASM("object/effectlink", func_00345F90);

//63.33%
INCLUDE_ASM("object/effectlink", func_00346060__FPv);
#ifdef SKIP_ASM
int func_00346060(void* self)
{
    int t0 = 1;
    *(int*)((char*)self + 0x14) = t0;
    return t0;
}
#endif

INCLUDE_ASM("object/effectlink", func_00346070);

INCLUDE_ASM("object/effectlink", func_003460A0);

INCLUDE_ASM("object/effectlink", func_00346120);

INCLUDE_ASM("object/effectlink", func_003461C0);

INCLUDE_ASM("object/effectlink", func_00346228);

INCLUDE_ASM("object/effectlink", func_00346258);

INCLUDE_ASM("object/effectlink", func_003462A0);

INCLUDE_ASM("object/effectlink", func_00346300);

INCLUDE_ASM("object/effectlink", func_00346350);

INCLUDE_ASM("object/effectlink", func_003464E0);

INCLUDE_ASM("object/effectlink", func_00346568);

