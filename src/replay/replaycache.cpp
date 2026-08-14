#include "common.h"

INCLUDE_ASM("replay/replaycache", cReplay_addCache);

INCLUDE_ASM("replay/replaycache", func_002700D8);

INCLUDE_ASM("replay/replaycache", func_00270130);

INCLUDE_ASM("replay/replaycache", func_002701A0);

INCLUDE_ASM("replay/replaycache", func_00270238);

INCLUDE_ASM("replay/replaycache", func_00270280);

INCLUDE_ASM("replay/replaycache", func_002702F8);

INCLUDE_ASM("replay/replaycache", func_00270378);

INCLUDE_ASM("replay/replaycache", func_002703F0);

INCLUDE_ASM("replay/replaycache", func_00270538);

//100%
INCLUDE_ASM("replay/replaycache", func_002705A8__FPv);
#ifdef SKIP_ASM
void func_002705A8(void* self)
{
}
#endif

INCLUDE_ASM("replay/replaycache", func_002705B0);

INCLUDE_ASM("replay/replaycache", func_00270628);

//100%
INCLUDE_ASM("replay/replaycache", func_00270658);
#ifdef SKIP_ASM
extern "C" void func_00270658(void* self)
{
    if (*(int*)((char*)self + 0x620) == 0) {
        *(int*)((char*)self + 0x624) = 1;
    }
}
#endif

INCLUDE_ASM("replay/replaycache", func_00270670);

INCLUDE_ASM("replay/replaycache", func_002706B8);

extern "C" void func_0026F980(void* self);
extern "C" void func_0026F4A0(void* self, int arg);

//100%
INCLUDE_ASM("replay/replaycache", cReplay_stopAutoReplay__FPv);
#ifdef SKIP_ASM
void cReplay_stopAutoReplay(void* self)
{
    if (*(int*)((char*)self + 0x61C) != 0) {
        func_0026F980(self);
    }
    func_0026F4A0(self, 0xD);
}
#endif

INCLUDE_ASM("replay/replaycache", func_00270730);

INCLUDE_ASM("replay/replaycache", func_002707E0);

INCLUDE_ASM("replay/replaycache", func_00270870);

INCLUDE_ASM("replay/replaycache", func_002708F0);

INCLUDE_ASM("replay/replaycache", func_00270970);

INCLUDE_ASM("replay/replaycache", func_002709D8);

INCLUDE_ASM("replay/replaycache", func_00270AB0);

INCLUDE_ASM("replay/replaycache", func_00270B88);

INCLUDE_ASM("replay/replaycache", func_00270BD8);

//100%
INCLUDE_ASM("replay/replaycache", func_00270C40);
#ifdef SKIP_ASM
extern "C" int func_00270C40(void* self, int a1)
{
    if (a1 != 0) {
        return *(int*)((char*)self + 0xc);
    }
    return 1;
}
#endif

INCLUDE_ASM("replay/replaycache", func_00270C58);

INCLUDE_ASM("replay/replaycache", func_00270CE8);

INCLUDE_ASM("replay/replaycache", func_00270DE0);

INCLUDE_ASM("replay/replaycache", func_00270E18);

INCLUDE_ASM("replay/replaycache", func_00270E68);

extern "C" void* func_00270F78(void* self);

//100%
INCLUDE_ASM("replay/replaycache", func_00270ED8__FPv);
#ifdef SKIP_ASM
void* func_00270ED8(void* self)
{
    return func_00270F78(self);
}
#endif

extern "C" void* func_0026F228(void* self);

//100%
INCLUDE_ASM("replay/replaycache", func_00270EF8__FPv);
#ifdef SKIP_ASM
void* func_00270EF8(void* self)
{
    return func_0026F228(self);
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_00270F18__FPv);
#ifdef SKIP_ASM
void func_00270F18(void* self)
{
}
#endif

INCLUDE_ASM("replay/replaycache", func_00270F20);

INCLUDE_ASM("replay/replaycache", func_00270F78);

INCLUDE_ASM("replay/replaycache", func_00270FC0);

INCLUDE_ASM("replay/replaycache", func_00271058);

INCLUDE_ASM("replay/replaycache", func_002710A8);

INCLUDE_ASM("replay/replaycache", func_00271228);

INCLUDE_ASM("replay/replaycache", func_002712C0);

INCLUDE_ASM("replay/replaycache", func_002712F8);

INCLUDE_ASM("replay/replaycache", func_00271348);

INCLUDE_ASM("replay/replaycache", func_00271380);

INCLUDE_ASM("replay/replaycache", func_002714E0);

INCLUDE_ASM("replay/replaycache", func_00271510);

INCLUDE_ASM("replay/replaycache", func_00271620);

INCLUDE_ASM("replay/replaycache", func_00271688);

//100%
INCLUDE_ASM("replay/replaycache", func_002716F0__FPv);
#ifdef SKIP_ASM
void* func_002716F0(void* self)
{
    int t0 = 0;
    void* t1 = (char*)*(void**)((char*)self + 0x638) + 0x1;
    *(int*)((char*)self + 0x644) = t0;
    *(int*)((char*)self + 0x648) = t0;
    *(int*)((char*)self + 0x638) = (int)t1;
    return t1;
}
#endif

INCLUDE_ASM("replay/replaycache", func_00271708);

INCLUDE_ASM("replay/replaycache", func_00271758);

INCLUDE_ASM("replay/replaycache", func_002718E8);

INCLUDE_ASM("replay/replaycache", func_002721D0);

INCLUDE_ASM("replay/replaycache", func_00272258);

INCLUDE_ASM("replay/replaycache", func_00272288);

extern "C" void* func_002718E8(int, int);

//99.38%
INCLUDE_ASM("replay/replaycache", func_002722C0__FPv);
#ifdef SKIP_ASM
void* func_002722C0(void* self)
{
    return func_002718E8(1, 0xffff);
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_002722E0__FPvN20);
#ifdef SKIP_ASM
void* func_002722E0(void* self, void* a1, void* a2)
{
    *(int*)((char*)self + 0x8) = (int)a1;
    *(int*)self = (int)a1;
    *(int*)((char*)self + 0x4) = (int)a2;
    *(int*)((char*)a1 + 0x4) = 0;
    *(int*)*(void**)((char*)self + 0x8) = (int)((char*)a2 - 0x8);
    return self;
}
#endif

INCLUDE_ASM("replay/replaycache", func_00272308);

INCLUDE_ASM("replay/replaycache", func_002723A8);

INCLUDE_ASM("replay/replaycache", func_00272488);

extern "C" void* func_00272488(void* self);

//99.29%
INCLUDE_ASM("replay/replaycache", func_002724C8__FPv);
#ifdef SKIP_ASM
void* func_002724C8(void* self)
{
    return func_00272488(self);
}
#endif

INCLUDE_ASM("replay/replaycache", func_002724E8);

extern "C" void* func_002724E8(void* self);

//99.29%
INCLUDE_ASM("replay/replaycache", func_00272510__FPv);
#ifdef SKIP_ASM
void* func_00272510(void* self)
{
    return func_002724E8(self);
}
#endif

INCLUDE_ASM("replay/replaycache", func_00272570);

INCLUDE_ASM("replay/replaycache", func_002725B8);

INCLUDE_ASM("replay/replaycache", func_002725F0);

//99.11%
INCLUDE_ASM("replay/replaycache", func_00272680__FPv);
#ifdef SKIP_ASM
void func_00272680(void* self)
{
    int t0 = 0;
    *(int*)((char*)self + 0x24) = t0;
    *(int*)((char*)self + 0x8) = t0;
    *(int*)((char*)self + 0xc) = t0;
    *(int*)((char*)self + 0x10) = t0;
    *(int*)((char*)self + 0x14) = t0;
    *(int*)((char*)self + 0x18) = t0;
    *(int*)((char*)self + 0x1c) = t0;
    *(int*)((char*)self + 0x20) = t0;
}
#endif

INCLUDE_ASM("replay/replaycache", func_002726A8);

INCLUDE_ASM("replay/replaycache", func_00272788);

INCLUDE_ASM("replay/replaycache", func_002728D0);

INCLUDE_ASM("replay/replaycache", func_002728F8);

INCLUDE_ASM("replay/replaycache", func_00272938);

INCLUDE_ASM("replay/replaycache", func_002729A8);

INCLUDE_ASM("replay/replaycache", func_00272AD0);

INCLUDE_ASM("replay/replaycache", func_00272B58);

//100%
INCLUDE_ASM("replay/replaycache", func_00272CC0);
#ifdef SKIP_ASM
extern "C" void* func_00272CC0(void* self, int a1)
{
    char* base = *(char**)((char*)self + 0x14);
    char* p = base + a1 * 0x58;
    return *(int*)(p + 0xc) != 0 ? p + 0x8 : 0;
}
#endif

INCLUDE_ASM("replay/replaycache", func_00272D68);

INCLUDE_ASM("replay/replaycache", func_00272DA0);

INCLUDE_ASM("replay/replaycache", func_00272DF0);

INCLUDE_ASM("replay/replaycache", func_00272EC0);

INCLUDE_ASM("replay/replaycache", func_00272F28);

INCLUDE_ASM("replay/replaycache", func_00273040);

INCLUDE_ASM("replay/replaycache", func_002730C0);

INCLUDE_ASM("replay/replaycache", func_00273140);

INCLUDE_ASM("replay/replaycache", func_00273180);

INCLUDE_ASM("replay/replaycache", func_002731B8);

INCLUDE_ASM("replay/replaycache", func_00273208);

INCLUDE_ASM("replay/replaycache", func_002732C8);

INCLUDE_ASM("replay/replaycache", func_00273330);

INCLUDE_ASM("replay/replaycache", func_002733E0);

INCLUDE_ASM("replay/replaycache", func_00273418);

INCLUDE_ASM("replay/replaycache", func_00273468);

INCLUDE_ASM("replay/replaycache", func_002734A8);

INCLUDE_ASM("replay/replaycache", func_002734E0);

INCLUDE_ASM("replay/replaycache", func_00273530);

INCLUDE_ASM("replay/replaycache", func_00273630);

INCLUDE_ASM("replay/replaycache", func_00273698);

INCLUDE_ASM("replay/replaycache", func_002737E0);

INCLUDE_ASM("replay/replaycache", func_00273860);

INCLUDE_ASM("replay/replaycache", func_002738F8);

INCLUDE_ASM("replay/replaycache", func_00273938);

INCLUDE_ASM("replay/replaycache", func_00273970);

INCLUDE_ASM("replay/replaycache", func_002739B8);

INCLUDE_ASM("replay/replaycache", func_00273A00);

INCLUDE_ASM("replay/replaycache", func_00273A60);

INCLUDE_ASM("replay/replaycache", func_00273AA8);

INCLUDE_ASM("replay/replaycache", func_00273D20);

INCLUDE_ASM("replay/replaycache", func_00273DC0);

INCLUDE_ASM("replay/replaycache", func_00273F68);

INCLUDE_ASM("replay/replaycache", func_00274100);

INCLUDE_ASM("replay/replaycache", func_00274240);

//100%
INCLUDE_ASM("replay/replaycache", func_002742C8__FPvi);
#ifdef SKIP_ASM
int func_002742C8(void* self, int a1)
{
    return *(int*)((char*)*(void**)((char*)self + 0x24) + a1 * 4);
}
#endif

INCLUDE_ASM("replay/replaycache", func_002742E0);

//100%
INCLUDE_ASM("replay/replaycache", func_00274348__FPv);
#ifdef SKIP_ASM
int func_00274348(void* self)
{
    return *(int*)((char*)*(void**)((char*)self + 0x1c) + 0x4);
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_00274388__FPv);
#ifdef SKIP_ASM
int func_00274388(void* self)
{
    return *(int*)((char*)*(void**)((char*)self + 0x10) + 0x4);
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_002743C8__FPv);
#ifdef SKIP_ASM
unsigned char func_002743C8(void* self)
{
    return *(unsigned char*)((char*)*(void**)((char*)self + 0x1c) + 0x3);
}
#endif

INCLUDE_ASM("replay/replaycache", func_002743E8);

INCLUDE_ASM("replay/replaycache", func_00274518);

INCLUDE_ASM("replay/replaycache", func_002745C0);

INCLUDE_ASM("replay/replaycache", func_002746F8);

//100%
INCLUDE_ASM("replay/replaycache", func_00274808__FPvf);
#ifdef SKIP_ASM
void func_00274808(void* self, float val)
{
    *(float*)((char*)self + 0x24) = val;
}
#endif

extern "C" void* func_00274830(void*, int);

//100%
INCLUDE_ASM("replay/replaycache", func_00274810__FPv);
#ifdef SKIP_ASM
void* func_00274810(void* self)
{
    return func_00274830(self, *(int*)((char*)self + 0x1c));
}
#endif

INCLUDE_ASM("replay/replaycache", func_00274830);

INCLUDE_ASM("replay/replaycache", func_00274918);

//100%
INCLUDE_ASM("replay/replaycache", func_002749E8);
#ifdef SKIP_ASM
extern "C" void func_002749E8(void* self)
{
    if (*(int*)((char*)self + 0x20) != 0) {
        *(int*)((char*)self + 0x2c) += 1;
    }
}
#endif

INCLUDE_ASM("replay/replaycache", func_00274A08);

INCLUDE_ASM("replay/replaycache", func_00274A30);

//78.33%
INCLUDE_ASM("replay/replaycache", func_00274C10__FPvi);
#ifdef SKIP_ASM
int func_00274C10(void* self, int a1)
{
    *(int*)((char*)self + 0xc) = a1;
    return *(int*)((char*)self + 0xc);
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_00274C20);
#ifdef SKIP_ASM
extern "C" void* func_00274C20(void* self, int a1)
{
    return *(char**)((char*)self + 0x18) + a1 * 0x3c;
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_00274C38);
#ifdef SKIP_ASM
extern "C" void* func_00274C38(void* self)
{
    if (*(unsigned short*)((char*)self + 0x2) >= 0xd) {
        return (char*)self + 0xc;
    }
    return 0;
}
#endif

INCLUDE_ASM("replay/replaycache", func_00274C70);

INCLUDE_ASM("replay/replaycache", func_00274D08);

//100%
INCLUDE_ASM("replay/replaycache", func_00274D70);
#ifdef SKIP_ASM
extern "C" int func_00274D70(void* self)
{
    int v = *(int*)((char*)self + 0x44);
    if (v != 0) {
        return v;
    }
    return **(int**)((char*)self + 0x8);
}
#endif

INCLUDE_ASM("replay/replaycache", func_00274DE0);

INCLUDE_ASM("replay/replaycache", func_002751A0);

//100%
INCLUDE_ASM("replay/replaycache", func_002752F0__FPv);
#ifdef SKIP_ASM
void* func_002752F0(void* self)
{
    return (char*)self + 0x1C;
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_002752F8__FPv);
#ifdef SKIP_ASM
int func_002752F8(void* self)
{
    return *(int*)((char*)self + 0x20);
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_00275300__FPv);
#ifdef SKIP_ASM
int func_00275300(void* self)
{
    return -0x1;
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_00275308__FPv);
#ifdef SKIP_ASM
int func_00275308(void* self)
{
    return 0;
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_00275310__FPv);
#ifdef SKIP_ASM
int func_00275310(void* self)
{
    return *(int*)((char*)self + 0xC);
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_00275318__FPv);
#ifdef SKIP_ASM
int func_00275318(void* self)
{
    return (*(int*)((char*)self + 0x8) != 0);
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_00275328__FPv);
#ifdef SKIP_ASM
void* func_00275328(void* self)
{
    return (char*)self + 0x28;
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_00275330__FPv);
#ifdef SKIP_ASM
int func_00275330(void* self)
{
    return *(int*)((char*)self + 0x24);
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_00275338__FPv);
#ifdef SKIP_ASM
int func_00275338(void* self)
{
    return 0x2;
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_00275340__FPv);
#ifdef SKIP_ASM
int func_00275340(void* self)
{
    return *(int*)((char*)self + 0xC);
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_00275348__FPv);
#ifdef SKIP_ASM
int func_00275348(void* self)
{
    return (*(int*)((char*)self + 0x8) != 0);
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_00275358__FPv);
#ifdef SKIP_ASM
void* func_00275358(void* self)
{
    return (char*)self + 0x20;
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_00275360__FPv);
#ifdef SKIP_ASM
int func_00275360(void* self)
{
    return *(int*)((char*)self + 0x1C);
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_00275368__FPv);
#ifdef SKIP_ASM
int func_00275368(void* self)
{
    return 0x3;
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_00275370__FPv);
#ifdef SKIP_ASM
int func_00275370(void* self)
{
    return *(int*)((char*)self + 0xC);
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_00275378__FPv);
#ifdef SKIP_ASM
int func_00275378(void* self)
{
    return (*(int*)((char*)self + 0x8) != 0);
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_00275388__FPv);
#ifdef SKIP_ASM
void* func_00275388(void* self)
{
    return (char*)self + 0x24;
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_00275390__FPv);
#ifdef SKIP_ASM
int func_00275390(void* self)
{
    return *(int*)((char*)self + 0x20);
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_00275398__FPv);
#ifdef SKIP_ASM
int func_00275398(void* self)
{
    return 0x1;
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_002753A0__FPv);
#ifdef SKIP_ASM
int func_002753A0(void* self)
{
    return *(int*)((char*)self + 0xC);
}
#endif

//100%
INCLUDE_ASM("replay/replaycache", func_002753A8__FPv);
#ifdef SKIP_ASM
int func_002753A8(void* self)
{
    return (*(int*)((char*)self + 0x8) != 0);
}
#endif

