#include "common.h"

//100%
//https://decomp.me/scratch/fZ4tu
INCLUDE_ASM("dirtysock/tags", cDirtysock_tag__TagFieldSetupAppend__FPcN20);
#ifdef SKIP_ASM
char* cDirtysock_tag__TagFieldSetupAppend(char* message, char* buffer, char* key)
{
    if (key == (char*)0x0) {
        *message = 0;
    }
    else {
        while (*key != 0x0) {
            *buffer = *key;
            key = key + 1;
            buffer = buffer + 1;
        }
        *buffer = '=';
        buffer = buffer + 1;
    }
    return buffer;
}
#endif

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag__TagFieldSetupTerm);

INCLUDE_ASM("dirtysock/tags", func_003EB578);

INCLUDE_ASM("dirtysock/tags", func_003EB588);

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldFind);

INCLUDE_ASM("dirtysock/tags", func_003EB840);

INCLUDE_ASM("dirtysock/tags", func_003EB8B8);

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldDelete);

INCLUDE_ASM("dirtysock/tags", func_003EB9E8);

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldDupl);

INCLUDE_ASM("dirtysock/tags", func_003EBBA8);

INCLUDE_ASM("dirtysock/tags", func_003EBCB0);

INCLUDE_ASM("dirtysock/tags", func_003EBD70);

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldSetNumber);

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldSetFlags);

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldSetAddress);

//23.48%
//https://decomp.me/scratch/KjMXX
INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldSetFourCC);

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldSetString);

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldSetBinary);

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldSetStructure);

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldSetCrypt);

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldSetEpoch);

INCLUDE_ASM("dirtysock/tags", func_003EC8B8);

INCLUDE_ASM("dirtysock/tags", func_003EC9A0);

INCLUDE_ASM("dirtysock/tags", func_003ECA88);

INCLUDE_ASM("dirtysock/tags", func_003ECB00);

INCLUDE_ASM("dirtysock/tags", func_003ECBD8);

INCLUDE_ASM("dirtysock/tags", func_003ECE38);

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldGetNumber);

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldGetFlags);

//56.50%
//https://decomp.me/scratch/98Kir
INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldGetAddr);

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldGetFourCC);

INCLUDE_ASM("dirtysock/tags", func_003ED0F8);

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldGetString);

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldGetBinary);

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldGetStructure);

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldGetCrypt);

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldGetTime);

INCLUDE_ASM("dirtysock/tags", func_003EDD70);

INCLUDE_ASM("dirtysock/tags", func_003EDE80);
