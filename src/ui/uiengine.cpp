#include "common.h"

//100%
INCLUDE_ASM("ui/uiengine", UIAsciiToUnicode__FPUsPCc);
#ifdef SKIP_ASM
void UIAsciiToUnicode(unsigned short* dst, const char* src)
{
    for (; *src != 0; src++, dst++) {
        *dst = (char)*(unsigned char*)src;
    }
    *dst = 0;
}
#endif

INCLUDE_ASM("ui/uiengine", func_00397B08);

INCLUDE_ASM("ui/uiengine", func_00397B70);

INCLUDE_ASM("ui/uiengine", cUIEngine_loadFile);

INCLUDE_ASM("ui/uiengine", cUIEngine_addScreenByHashName);

INCLUDE_ASM("ui/uiengine", func_00397DF8);

INCLUDE_ASM("ui/uiengine", func_00398018);

INCLUDE_ASM("ui/uiengine", func_00398038);

INCLUDE_ASM("ui/uiengine", func_00398078);

INCLUDE_ASM("ui/uiengine", cUITextureBank_setData);

INCLUDE_ASM("ui/uiengine", func_00398380);

INCLUDE_ASM("ui/uiengine", func_003983F0);

INCLUDE_ASM("ui/uiengine", func_00398438);

INCLUDE_ASM("ui/uiengine", func_003984B0);

INCLUDE_ASM("ui/uiengine", cUIFontInterface_loadFonts);

extern "C" void* func_0039FE00(void* self);

//100%
INCLUDE_ASM("ui/uiengine", func_00398618__FPv);
#ifdef SKIP_ASM
void* func_00398618(void* self)
{
    return func_0039FE00(self);
}
#endif

INCLUDE_ASM("ui/uiengine", func_00398638);

INCLUDE_ASM("ui/uiengine", func_003986B0);

INCLUDE_ASM("ui/uiengine", func_00398738);

INCLUDE_ASM("ui/uiengine", func_00398798);

INCLUDE_ASM("ui/uiengine", func_003987F8);

INCLUDE_ASM("ui/uiengine", func_00398868);

INCLUDE_ASM("ui/uiengine", func_00398910);

INCLUDE_ASM("ui/uiengine", func_00398998);

//58.0%
INCLUDE_ASM("ui/uiengine", func_00398A60__FPvT0);
#ifdef SKIP_ASM
float func_00398A60(void* self, void* a1)
{
    float t0 = *(float*)a1;
    *(float*)self = t0;
    *(float*)a1 = *(float*)self;
    return t0;
}
#endif

INCLUDE_ASM("ui/uiengine", func_00398A78);

INCLUDE_ASM("ui/uiengine", func_00399730);

INCLUDE_ASM("ui/uiengine", func_00399768);

INCLUDE_ASM("ui/uiengine", func_00399820);

INCLUDE_ASM("ui/uiengine", func_00399920);

INCLUDE_ASM("ui/uiengine", func_00399970);

INCLUDE_ASM("ui/uiengine", func_00399D80);

INCLUDE_ASM("ui/uiengine", func_00399E28);

INCLUDE_ASM("ui/uiengine", func_00399F00);

