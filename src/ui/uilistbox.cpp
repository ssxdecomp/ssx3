#include "common.h"

INCLUDE_ASM("ui/uilistbox", cUIListBox_addEntryByAsciiString);

INCLUDE_ASM("ui/uilistbox", func_0039A4B0);

INCLUDE_ASM("ui/uilistbox", cUIListBox_addEntryByStringID);

INCLUDE_ASM("ui/uilistbox", func_0039A670);

INCLUDE_ASM("ui/uilistbox", func_0039A708);

INCLUDE_ASM("ui/uilistbox", func_0039A738);

INCLUDE_ASM("ui/uilistbox", func_0039A768);

//100%
INCLUDE_ASM("ui/uilistbox", func_0039A7A8);
#ifdef SKIP_ASM
extern "C" void func_0039A7A8(void* self, int a1)
{
    unsigned char v = (unsigned char)a1;
    if (v < *(unsigned char*)((char*)self + 0x318)) {
        *(char*)((char*)self + 0x319) = v;
    }
}
#endif

INCLUDE_ASM("ui/uilistbox", cUIListBox_setEntryByAsciiString);

INCLUDE_ASM("ui/uilistbox", func_0039A8D8);

INCLUDE_ASM("ui/uilistbox", func_0039A928);

INCLUDE_ASM("ui/uilistbox", func_0039AAC0);

INCLUDE_ASM("ui/uilistbox", func_0039AB00);

INCLUDE_ASM("ui/uilistbox", func_0039AB50);

INCLUDE_ASM("ui/uilistbox", func_0039AC48);

