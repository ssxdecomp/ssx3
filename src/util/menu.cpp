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

//100%
INCLUDE_ASM("util/menu", func_002CA368__FPv);
#ifdef SKIP_ASM
void func_002CA368(void* self)
{
}
#endif

//100%
INCLUDE_ASM("util/menu", func_002CA370__FPv);
#ifdef SKIP_ASM
void func_002CA370(void* self)
{
}
#endif

//100%
INCLUDE_ASM("util/menu", func_002CA378);
#ifdef SKIP_ASM
extern "C" int func_002CA378(void* self)
{
    return *(int*)((char*)self + 0x4) & 1;
}
#endif

INCLUDE_ASM("util/menu", func_002CA388);

//100%
INCLUDE_ASM("util/menu", func_002CA3B0);
#ifdef SKIP_ASM
extern "C" int func_002CA3B0(void* self)
{
    return *(int*)((char*)self + 0x4) & 8;
}
#endif

INCLUDE_ASM("util/menu", func_002CA3E8);

extern "C" void* func_002CC260(int);

//100%
INCLUDE_ASM("util/menu", func_002CA408__FPv);
#ifdef SKIP_ASM
void* func_002CA408(void* self)
{
    return func_002CC260(*(int*)((char*)*(void**)self + 0x124));
}
#endif

extern "C" void* func_002CC280(int);

//100%
INCLUDE_ASM("util/menu", func_002CA428__FPv);
#ifdef SKIP_ASM
void* func_002CA428(void* self)
{
    return func_002CC280(*(int*)((char*)*(void**)self + 0x124));
}
#endif

extern "C" void* func_002CC2A0(int);

//100%
INCLUDE_ASM("util/menu", func_002CA448__FPv);
#ifdef SKIP_ASM
void* func_002CA448(void* self)
{
    return func_002CC2A0(*(int*)((char*)*(void**)self + 0x124));
}
#endif

extern "C" void* func_002CC2C0(int);

//100%
INCLUDE_ASM("util/menu", func_002CA468__FPv);
#ifdef SKIP_ASM
void* func_002CA468(void* self)
{
    return func_002CC2C0(*(int*)((char*)*(void**)self + 0x124));
}
#endif

extern "C" void* func_002CC2E0(int);

//100%
INCLUDE_ASM("util/menu", func_002CA488__FPv);
#ifdef SKIP_ASM
void* func_002CA488(void* self)
{
    return func_002CC2E0(*(int*)((char*)*(void**)self + 0x124));
}
#endif

extern "C" void* func_002CC318(int);

//100%
INCLUDE_ASM("util/menu", func_002CA4A8__FPv);
#ifdef SKIP_ASM
void* func_002CA4A8(void* self)
{
    return func_002CC318(*(int*)((char*)*(void**)self + 0x124));
}
#endif

INCLUDE_ASM("util/menu", func_002CA4C8);

INCLUDE_ASM("util/menu", func_002CA768);

INCLUDE_ASM("util/menu", func_002CA988);

extern void* D_00486ED0[];

//100%
INCLUDE_ASM("util/menu", func_002CAA58__FPv);
#ifdef SKIP_ASM
void* func_002CAA58(void* self)
{
    int t0 = 0;
    *(int*)self = t0;
    *(int*)((char*)self + 0x12c) = (int)(void*)D_00486ED0;
    *(int*)((char*)self + 0x4) = t0;
    *(int*)((char*)self + 0x8) = t0;
    *(int*)((char*)self + 0x124) = t0;
    return self;
}
#endif

INCLUDE_ASM("util/menu", func_002CAA80);

INCLUDE_ASM("util/menu", func_002CAAB0);

INCLUDE_ASM("util/menu", func_002CAB08);

INCLUDE_ASM("util/menu", func_002CABE0);

INCLUDE_ASM("util/menu", func_002CACC0);

//100%
INCLUDE_ASM("util/menu", func_002CAD48__FPv);
#ifdef SKIP_ASM
int func_002CAD48(void* self)
{
    return 0;
}
#endif

//100%
INCLUDE_ASM("util/menu", func_002CAD50__FPv);
#ifdef SKIP_ASM
void func_002CAD50(void* self)
{
}
#endif

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

//98.4%
INCLUDE_ASM("util/menu", func_002CC070__FPv);
#ifdef SKIP_ASM
int func_002CC070(void* self)
{
    int t0 = -1;
    int t1 = 11;
    int t2 = 0;
    *(int*)((char*)self + 0x50) = t0;
    *(int*)((char*)self + 0x48) = t1;
    *(int*)((char*)self + 0x58) = t2;
    *(int*)((char*)self + 0x54) = t2;
    *(int*)self = t2;
    *(int*)((char*)self + 0x64) = t2;
    *(int*)((char*)self + 0x4c) = t0;
    return t1;
}
#endif

//100%
INCLUDE_ASM("util/menu", func_002CC098);
#ifdef SKIP_ASM
extern "C" int func_002CC098(void* self)
{
    int r = 0;
    if (*(int*)self != 0) {
        r = *(int*)((char*)self + 0x54) != 0;
    }
    return r;
}
#endif

//100%
INCLUDE_ASM("util/menu", func_002CC0B8__FPvi);
#ifdef SKIP_ASM
void func_002CC0B8(void* self, int val)
{
    *(int*)((char*)self + 0x54) = val;
}
#endif

INCLUDE_ASM("util/menu", func_002CC0C0);

//100%
INCLUDE_ASM("util/menu", func_002CC248__FPv);
#ifdef SKIP_ASM
int func_002CC248(void* self)
{
    return *(int*)((char*)self + 0x48);
}
#endif

//100%
INCLUDE_ASM("util/menu", func_002CC250__FPv);
#ifdef SKIP_ASM
int func_002CC250(void* self)
{
    return *(int*)((char*)self + 0x4C);
}
#endif

//100%
INCLUDE_ASM("util/menu", func_002CC258__FPv);
#ifdef SKIP_ASM
int func_002CC258(void* self)
{
    return *(int*)((char*)self + 0x50);
}
#endif

extern "C" void* func_00320BF0(int, int);

//100%
INCLUDE_ASM("util/menu", func_002CC260__FPv);
#ifdef SKIP_ASM
void* func_002CC260(void* self)
{
    return func_00320BF0(*(int*)((char*)self + 0x5c), 0x3e);
}
#endif

//100%
INCLUDE_ASM("util/menu", func_002CC280__FPv);
#ifdef SKIP_ASM
void* func_002CC280(void* self)
{
    return func_00320BF0(*(int*)((char*)self + 0x5c), 0x3f);
}
#endif

//100%
INCLUDE_ASM("util/menu", func_002CC2A0__FPv);
#ifdef SKIP_ASM
void* func_002CC2A0(void* self)
{
    return func_00320BF0(*(int*)((char*)self + 0x5c), 0x40);
}
#endif

//100%
INCLUDE_ASM("util/menu", func_002CC2C0__FPv);
#ifdef SKIP_ASM
void* func_002CC2C0(void* self)
{
    return func_00320BF0(*(int*)((char*)self + 0x5c), 0x41);
}
#endif

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

extern "C" void* func_002CA988(void*, int, int, int);

//88.33%
INCLUDE_ASM("util/menu", func_002CCDC8__FPvi);
#ifdef SKIP_ASM
void* func_002CCDC8(void* self, int a1)
{
    return func_002CA988(self, a1, 0, *(int*)((char*)self + 0x14));
}
#endif

INCLUDE_ASM("util/menu", func_002CCDF0);

INCLUDE_ASM("util/menu", func_002CCE38);

INCLUDE_ASM("util/menu", func_002CCEA8);

//88.33%
INCLUDE_ASM("util/menu", func_002CCEE0__FPvi);
#ifdef SKIP_ASM
void* func_002CCEE0(void* self, int a1)
{
    return func_002CA988(self, a1, 0, *(int*)((char*)self + 0x14));
}
#endif

INCLUDE_ASM("util/menu", func_002CCF08);

INCLUDE_ASM("util/menu", func_002CCF98);

INCLUDE_ASM("util/menu", func_002CD008);

INCLUDE_ASM("util/menu", func_002CD090);

INCLUDE_ASM("util/menu", func_002CD0E8);

INCLUDE_ASM("util/menu", func_002CD1D0);

INCLUDE_ASM("util/menu", func_002CD240);

extern void* D_004866C8[];
extern "C" void* func_002CA988(void*, int, int, int);

//59.5%
INCLUDE_ASM("util/menu", func_002CD278__FPvi);
#ifdef SKIP_ASM
void* func_002CD278(void* self, int a1)
{
    return func_002CA988(self, a1, *(int*)((char*)self + 0x14), 0);
}
#endif

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

//100%
INCLUDE_ASM("util/menu", func_002CD2E8__FPv);
#ifdef SKIP_ASM
int func_002CD2E8(void* self)
{
    return 0;
}
#endif

INCLUDE_ASM("util/menu", func_002CD2F0);

//88.33%
INCLUDE_ASM("util/menu", func_002CD328__FPvi);
#ifdef SKIP_ASM
void* func_002CD328(void* self, int a1)
{
    return func_002CA988(self, a1, 0, *(int*)((char*)self + 0x14));
}
#endif

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

//100%
INCLUDE_ASM("util/menu", func_002CD398__FPv);
#ifdef SKIP_ASM
int func_002CD398(void* self)
{
    return 0;
}
#endif

INCLUDE_ASM("util/menu", func_002CD3A0);

//100%
INCLUDE_ASM("util/menu", func_002CD3F0__FPv);
#ifdef SKIP_ASM
void func_002CD3F0(void* self)
{
}
#endif

INCLUDE_ASM("util/menu", func_002CD578);

INCLUDE_ASM("util/menu", func_002CD5A0);

INCLUDE_ASM("util/menu", func_002CD7B8);

INCLUDE_ASM("util/menu", func_002CD7F0);

INCLUDE_ASM("util/menu", cIntMenuItem_cIntMenuItem);

//100%
INCLUDE_ASM("util/menu", func_002CD9B8);
#ifdef SKIP_ASM
extern "C" void func_002CD9B8(void* self)
{
    int* p = *(int**)((char*)self + 0x18);
    int v = *(int*)((char*)self + 0x1c);
    if (v <= 0) {
        *p = 0;
    } else {
        *p = v;
    }
}
#endif

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

//100%
INCLUDE_ASM("util/menu", func_002CFF80__FPv);
#ifdef SKIP_ASM
int func_002CFF80(void* self)
{
    return 0;
}
#endif

INCLUDE_ASM("util/menu", func_002CFF88);

INCLUDE_ASM("util/menu", func_002D0008);

INCLUDE_ASM("util/menu", cARGBMenuItem_cARGBMenuItem);

extern "C" void* func_002CFA08(void* self);

//99.29%
INCLUDE_ASM("util/menu", func_002D03D0__FPv);
#ifdef SKIP_ASM
void* func_002D03D0(void* self)
{
    return func_002CFA08(self);
}
#endif

//100%
INCLUDE_ASM("util/menu", func_002D0448__FPv);
#ifdef SKIP_ASM
int func_002D0448(void* self)
{
    return 0;
}
#endif

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

extern "C" void* func_002FC2C0(void* self);

//100%
INCLUDE_ASM("util/menu", func_002D1CC0__FPv);
#ifdef SKIP_ASM
void* func_002D1CC0(void* self)
{
    return func_002FC2C0(self);
}
#endif

