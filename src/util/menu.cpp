#include "common.h"

struct cMenuItem {
    char pad_0x00[0x4];
    int field_0x4;
    void* field_0x8;
    int field_0xC;
    void* vtable; // 0x10
};
extern void* D_00486F28[16];

//100%
INCLUDE_ASM("util/menu", cMenuItem_cMenuItem__FP9cMenuItemPv);
#ifdef SKIP_ASM
cMenuItem* cMenuItem_cMenuItem(cMenuItem* self, void* text)
{
    self->field_0x4 = 1;
    self->vtable = D_00486F28;
    self->field_0x8 = text;
    self->field_0xC = 0;
    return self;
}
#endif

INCLUDE_ASM("util/menu", func_002CA280);

INCLUDE_ASM("util/menu", func_002CA2B0);

INCLUDE_ASM("util/menu", func_002CA320);

INCLUDE_ASM("util/menu", func_002CA368);

INCLUDE_ASM("util/menu", func_002CA370);

INCLUDE_ASM("util/menu", func_002CA378);

INCLUDE_ASM("util/menu", func_002CA388);

INCLUDE_ASM("util/menu", func_002CA3B0);

INCLUDE_ASM("util/menu", func_002CA3E8);

INCLUDE_ASM("util/menu", func_002CA408);

INCLUDE_ASM("util/menu", func_002CA428);

INCLUDE_ASM("util/menu", func_002CA448);

INCLUDE_ASM("util/menu", func_002CA468);

INCLUDE_ASM("util/menu", func_002CA488);

INCLUDE_ASM("util/menu", func_002CA4A8);

INCLUDE_ASM("util/menu", func_002CA4C8);

INCLUDE_ASM("util/menu", func_002CA768);

INCLUDE_ASM("util/menu", func_002CA988);

INCLUDE_ASM("util/menu", func_002CAA58);

INCLUDE_ASM("util/menu", func_002CAA80);

INCLUDE_ASM("util/menu", func_002CAAB0);

INCLUDE_ASM("util/menu", func_002CAB08);

INCLUDE_ASM("util/menu", func_002CABE0);

INCLUDE_ASM("util/menu", func_002CACC0);

INCLUDE_ASM("util/menu", func_002CAD48);

INCLUDE_ASM("util/menu", func_002CAD50);

INCLUDE_ASM("util/menu", func_002CAD58);

INCLUDE_ASM("util/menu", func_002CB180);

INCLUDE_ASM("util/menu", func_002CB2F8);

INCLUDE_ASM("util/menu", func_002CB350);

INCLUDE_ASM("util/menu", func_002CB498);

INCLUDE_ASM("util/menu", func_002CB880);

INCLUDE_ASM("util/menu", func_002CB8C8);

INCLUDE_ASM("util/menu", func_002CBAC8);

INCLUDE_ASM("util/menu", cMenu_addItem);

INCLUDE_ASM("util/menu", func_002CBE68);

INCLUDE_ASM("util/menu", func_002CBF08);

INCLUDE_ASM("util/menu", func_002CBF30);

INCLUDE_ASM("util/menu", func_002CBF60);

INCLUDE_ASM("util/menu", func_002CBFD0);

INCLUDE_ASM("util/menu", func_002CC018);

INCLUDE_ASM("util/menu", func_002CC048);

INCLUDE_ASM("util/menu", func_002CC070);

INCLUDE_ASM("util/menu", func_002CC098);

INCLUDE_ASM("util/menu", func_002CC0B8);

INCLUDE_ASM("util/menu", func_002CC0C0);

INCLUDE_ASM("util/menu", func_002CC248);

INCLUDE_ASM("util/menu", func_002CC250);

INCLUDE_ASM("util/menu", func_002CC258);

INCLUDE_ASM("util/menu", func_002CC260);

INCLUDE_ASM("util/menu", func_002CC280);

INCLUDE_ASM("util/menu", func_002CC2A0);

INCLUDE_ASM("util/menu", func_002CC2C0);

INCLUDE_ASM("util/menu", func_002CC2E0);

INCLUDE_ASM("util/menu", func_002CC318);

INCLUDE_ASM("util/menu", func_002CC350);

INCLUDE_ASM("util/menu", func_002CC3B8);

INCLUDE_ASM("util/menu", func_002CC460);

INCLUDE_ASM("util/menu", func_002CC578);

INCLUDE_ASM("util/menu", func_002CC648);

INCLUDE_ASM("util/menu", func_002CC758);

INCLUDE_ASM("util/menu", func_002CC8F0);

INCLUDE_ASM("util/menu", func_002CCB18);

INCLUDE_ASM("util/menu", func_002CCC38);

INCLUDE_ASM("util/menu", cSubMenuItem_cSubMenuItem);

INCLUDE_ASM("util/menu", func_002CCD20);

INCLUDE_ASM("util/menu", func_002CCD90);

INCLUDE_ASM("util/menu", func_002CCDC8);

INCLUDE_ASM("util/menu", func_002CCDF0);

INCLUDE_ASM("util/menu", func_002CCE38);

INCLUDE_ASM("util/menu", func_002CCEA8);

INCLUDE_ASM("util/menu", func_002CCEE0);

INCLUDE_ASM("util/menu", func_002CCF08);

INCLUDE_ASM("util/menu", func_002CCF98);

INCLUDE_ASM("util/menu", func_002CD008);

INCLUDE_ASM("util/menu", func_002CD090);

INCLUDE_ASM("util/menu", func_002CD0E8);

INCLUDE_ASM("util/menu", func_002CD1D0);

INCLUDE_ASM("util/menu", func_002CD240);

INCLUDE_ASM("util/menu", func_002CD278);

extern void* D_00486CA0[16];

struct cNullMenuItem {
    char pad_0x00[0x10];
    void* vtable;
    void* field_0x14;
};

//89.33% - target uses single-instruction addiu for the -1 constant, ours uses lui/ori for the void* constant
INCLUDE_ASM("util/menu", cNullMenuItem_cNullMenuItem__FP13cNullMenuItemPv);
#ifdef SKIP_ASM
cNullMenuItem* cNullMenuItem_cNullMenuItem(cNullMenuItem* self, void* text)
{
    cMenuItem_cMenuItem((cMenuItem*)self, (void*)-1);
    self->field_0x14 = text;
    self->vtable = D_00486CA0;
    return self;
}
#endif

INCLUDE_ASM("util/menu", func_002CD2E8);

INCLUDE_ASM("util/menu", func_002CD2F0);

INCLUDE_ASM("util/menu", func_002CD328);

extern void* D_00486C50[16];

struct cSpaceMenuItem {
    char pad_0x00[0x10];
    void* vtable;
    void* field_0x14;
};

//89.33% - same -1 constant materialization issue as cNullMenuItem
INCLUDE_ASM("util/menu", cSpaceMenuItem_cSpaceMenuItem__FP14cSpaceMenuItemPv);
#ifdef SKIP_ASM
cSpaceMenuItem* cSpaceMenuItem_cSpaceMenuItem(cSpaceMenuItem* self, void* text)
{
    cMenuItem_cMenuItem((cMenuItem*)self, (void*)-1);
    self->field_0x14 = text;
    self->vtable = D_00486C50;
    return self;
}
#endif

INCLUDE_ASM("util/menu", func_002CD398);

INCLUDE_ASM("util/menu", func_002CD3A0);

INCLUDE_ASM("util/menu", func_002CD3F0);

INCLUDE_ASM("util/menu", func_002CD578);

INCLUDE_ASM("util/menu", func_002CD5A0);

INCLUDE_ASM("util/menu", func_002CD7B8);

INCLUDE_ASM("util/menu", func_002CD7F0);

INCLUDE_ASM("util/menu", cIntMenuItem_cIntMenuItem);

INCLUDE_ASM("util/menu", func_002CD9B8);

INCLUDE_ASM("util/menu", func_002CD9D8);

INCLUDE_ASM("util/menu", func_002CDBF0);

INCLUDE_ASM("util/menu", func_002CDC28);

INCLUDE_ASM("util/menu", cFloatMenuItem_cFloatMenuItem);

INCLUDE_ASM("util/menu", func_002CDD78);

INCLUDE_ASM("util/menu", func_002CDF78);

INCLUDE_ASM("util/menu", func_002CDFA0);

INCLUDE_ASM("util/menu", func_002CDFD8);

INCLUDE_ASM("util/menu", func_002CE100);

INCLUDE_ASM("util/menu", func_002CE1F0);

INCLUDE_ASM("util/menu", func_002CE368);

INCLUDE_ASM("util/menu", cAngleMenuItem_render);

INCLUDE_ASM("util/menu", func_002CE418);

INCLUDE_ASM("util/menu", func_002CE488);

INCLUDE_ASM("util/menu", func_002CE820);

INCLUDE_ASM("util/menu", func_002CE910);

INCLUDE_ASM("util/menu", cColorMenuItem__cColorMenuItem);

INCLUDE_ASM("util/menu", func_002CED78);

INCLUDE_ASM("util/menu", func_002CEEE8);

INCLUDE_ASM("util/menu", func_002CF1C8);

INCLUDE_ASM("util/menu", func_002CF788);

INCLUDE_ASM("util/menu", func_002CF7B8);

INCLUDE_ASM("util/menu", func_002CF860);

INCLUDE_ASM("util/menu", func_002CF8D8);

void cMenu_addItem(void* menu, void* item);

//100%
INCLUDE_ASM("util/menu", cExpandMenuItem_addItem__FPvT0);
#ifdef SKIP_ASM
void cExpandMenuItem_addItem(void* self, void* item)
{
    cMenu_addItem((char*)self + 0x18, item);
}
#endif

INCLUDE_ASM("util/menu", func_002CFA08);

INCLUDE_ASM("util/menu", func_002CFAF8);

INCLUDE_ASM("util/menu", func_002CFB28);

INCLUDE_ASM("util/menu", func_002CFB58);

INCLUDE_ASM("util/menu", func_002CFD28);

INCLUDE_ASM("util/menu", func_002CFE78);

INCLUDE_ASM("util/menu", func_002CFEF8);

INCLUDE_ASM("util/menu", cRGBTitleMenuItem_cRGBTitleMenuItem);

INCLUDE_ASM("util/menu", func_002CFF80);

INCLUDE_ASM("util/menu", func_002CFF88);

INCLUDE_ASM("util/menu", func_002D0008);

INCLUDE_ASM("util/menu", cARGBMenuItem_cARGBMenuItem);

INCLUDE_ASM("util/menu", func_002D03D0);

INCLUDE_ASM("util/menu", func_002D0448);

INCLUDE_ASM("util/menu", func_002D0450);

INCLUDE_ASM("util/menu", func_002D0500);

INCLUDE_ASM("util/menu", func_002D06E8);

INCLUDE_ASM("util/menu", func_002D08E0);

INCLUDE_ASM("util/menu", func_002D0908);

INCLUDE_ASM("util/menu", func_002D0D48);

INCLUDE_ASM("util/menu", func_002D0EF8);

INCLUDE_ASM("util/menu", func_002D18B0);

INCLUDE_ASM("util/menu", func_002D1928);

INCLUDE_ASM("util/menu", func_002D19B8);

INCLUDE_ASM("util/menu", func_002D19E8);

INCLUDE_ASM("util/menu", func_002D1A30);

INCLUDE_ASM("util/menu", func_002D1AC8);

INCLUDE_ASM("util/menu", func_002D1AF0);

INCLUDE_ASM("util/menu", func_002D1B08);

INCLUDE_ASM("util/menu", func_002D1B30);

INCLUDE_ASM("util/menu", func_002D1B58);

INCLUDE_ASM("util/menu", func_002D1BA0);

INCLUDE_ASM("util/menu", func_002D1BD8);

INCLUDE_ASM("util/menu", func_002D1BE0);

INCLUDE_ASM("util/menu", func_002D1BF0);

INCLUDE_ASM("util/menu", func_002D1C20);

INCLUDE_ASM("util/menu", func_002D1C58);

INCLUDE_ASM("util/menu", func_002D1C70);

INCLUDE_ASM("util/menu", func_002D1C98);

INCLUDE_ASM("util/menu", func_002D1CB0);

INCLUDE_ASM("util/menu", func_002D1CC0);

