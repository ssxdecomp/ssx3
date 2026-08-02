#include "common.h"

signed char cBELibrary_getCharacterID(int index);

struct sCharWeightEntry {
    char pad_0x00[0x40];
    int mWeight;
    char pad_0x44[0x88 - 0x40 - 4];
};
extern sCharWeightEntry D_00530970[];

//98.67%
INCLUDE_ASM("be/beintcharacter", cBECharacterInterface_getWeight__FPvi);
#ifdef SKIP_ASM
int cBECharacterInterface_getWeight(void* self, int riderIndex)
{
    sCharWeightEntry* base = D_00530970;
    int charID = cBELibrary_getCharacterID(riderIndex);
    return base[charID].mWeight;
}
#endif

INCLUDE_ASM("be/beintcharacter", func_0014EF70);

INCLUDE_ASM("be/beintcharacter", func_0014EFA8);

