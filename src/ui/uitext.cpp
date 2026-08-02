#include "common.h"

INCLUDE_ASM("ui/uitext", cUIText_render2D);

INCLUDE_ASM("ui/uitext", cUIText_deleteText);

INCLUDE_ASM("ui/uitext", cUIText_getNumTextLines);

INCLUDE_ASM("ui/uitext", func_003A0C00);

INCLUDE_ASM("ui/uitext", func_003A0C28);

struct cUITextManager {
    char pad_0x00[0x28];
    short field_0x28;
    char pad_0x2A[2];
    void (*fn)(void*, int); // 0x2C
};

struct cUIText {
    char pad_0x00[0x8];
    cUITextManager* mMgr; // 0x8
    char pad_0xC[0xB0 - 0xC];
    int field_0xB0;
};

void cUIText_setAsciiStringPrivate(cUIText* self, const char* str);

//100%
INCLUDE_ASM("ui/uitext", cUIText_setAsciiString__FP7cUITextPCc);
#ifdef SKIP_ASM
void cUIText_setAsciiString(cUIText* self, const char* str)
{
    self->field_0xB0 = 0;
    cUIText_setAsciiStringPrivate(self, str);
}
#endif

INCLUDE_ASM("ui/uitext", cUIText_setAsciiStringPrivate);

INCLUDE_ASM("ui/uitext", func_003A0D00);

INCLUDE_ASM("ui/uitext", func_003A0E90);

INCLUDE_ASM("ui/uitext", cUIText_setUnicodeStringPrivate);

//100%
INCLUDE_ASM("ui/uitext", cUIText_setUnicodeStringByID__FP7cUITexti);
#ifdef SKIP_ASM
void cUIText_setUnicodeStringByID(cUIText* self, int id)
{
    self->field_0xB0 = id;
    cUITextManager* mgr = self->mMgr;
    mgr->fn((char*)self + mgr->field_0x28, 0);
}
#endif

INCLUDE_ASM("ui/uitext", func_003A1030);

INCLUDE_ASM("ui/uitext", func_003A1148);

INCLUDE_ASM("ui/uitext", func_003A11B8);

INCLUDE_ASM("ui/uitext", func_003A12D0);

INCLUDE_ASM("ui/uitext", func_003A1310);

INCLUDE_ASM("ui/uitext", func_003A1360);

INCLUDE_ASM("ui/uitext", func_003A13E0);

INCLUDE_ASM("ui/uitext", func_003A1588);

INCLUDE_ASM("ui/uitext", func_003A18C0);

INCLUDE_ASM("ui/uitext", func_003A1958);

INCLUDE_ASM("ui/uitext", func_003A19F8);

INCLUDE_ASM("ui/uitext", cUITextScroll_addUnicodeString);

INCLUDE_ASM("ui/uitext", func_003A1CF0);

INCLUDE_ASM("ui/uitext", func_003A1D30);

INCLUDE_ASM("ui/uitext", func_003A1F18);

INCLUDE_ASM("ui/uitext", func_003A1F90);

INCLUDE_ASM("ui/uitext", func_003A2068);

INCLUDE_ASM("ui/uitext", func_003A3280);

INCLUDE_ASM("ui/uitext", func_003A32F0);

INCLUDE_ASM("ui/uitext", func_003A3398);

