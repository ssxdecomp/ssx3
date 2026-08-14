#include "common.h"

INCLUDE_ASM("sound/bankmonitor", cBankMonitor_cBankMonitor);

INCLUDE_ASM("sound/bankmonitor", func_002ACE40);

INCLUDE_ASM("sound/bankmonitor", func_002ACF60);

INCLUDE_ASM("sound/bankmonitor", cBankMonitor_BANKMONITOR_Create);

INCLUDE_ASM("sound/bankmonitor", func_002AD2A8);

INCLUDE_ASM("sound/bankmonitor", func_002AD300);

INCLUDE_ASM("sound/bankmonitor", func_002AD398);

INCLUDE_ASM("sound/bankmonitor", func_002AD3C0);

INCLUDE_ASM("sound/bankmonitor", func_002AD410);

INCLUDE_ASM("sound/bankmonitor", func_002AD4D8);

INCLUDE_ASM("sound/bankmonitor", func_002AD550);

INCLUDE_ASM("sound/bankmonitor", func_002AD5F0);

INCLUDE_ASM("sound/bankmonitor", func_002AD650);

INCLUDE_ASM("sound/bankmonitor", func_002AD810);

//100%
INCLUDE_ASM("sound/bankmonitor", func_002AD848__FPv);
#ifdef SKIP_ASM
void* func_002AD848(void* self)
{
    *(int*)self = 0;
    *(int*)((char*)self + 0x4) = -1;
    return self;
}
#endif

INCLUDE_ASM("sound/bankmonitor", func_002AD860);

INCLUDE_ASM("sound/bankmonitor", func_002AD888);

//100%
INCLUDE_ASM("sound/bankmonitor", func_002AD930);
#ifdef SKIP_ASM
extern "C" int func_002AD930(void* self)
{
    return *(int*)((char*)self + 0x4) == -1;
}
#endif

INCLUDE_ASM("sound/bankmonitor", func_002AD940);

//99.33%
INCLUDE_ASM("sound/bankmonitor", func_002AD970__FPvi);
#ifdef SKIP_ASM
void func_002AD970(void* self, int a1)
{
    *(int*)((char*)self + 0x8) = a1;
    *(int*)((char*)self + 0x4) = a1;
}
#endif

//63.33%
INCLUDE_ASM("sound/bankmonitor", func_002AD980__FPv);
#ifdef SKIP_ASM
int func_002AD980(void* self)
{
    int t0 = 1;
    *(int*)self = t0;
    return t0;
}
#endif

//100%
INCLUDE_ASM("sound/bankmonitor", func_002AD990__FPv);
#ifdef SKIP_ASM
void func_002AD990(void* self)
{
    *(int*)((char*)self + 0x0) = 0;
}
#endif

INCLUDE_ASM("sound/bankmonitor", func_002AD998);

INCLUDE_ASM("sound/bankmonitor", func_002AD9C8);

INCLUDE_ASM("sound/bankmonitor", func_002ADAC8);

extern "C" void func_002AD998();
extern "C" void* func_003B5910(void*);

//98.75%
INCLUDE_ASM("sound/bankmonitor", func_002ADBF0__FPv);
#ifdef SKIP_ASM
void* func_002ADBF0(void* self)
{
    return func_003B5910((void*)func_002AD998);
}
#endif

//100%
INCLUDE_ASM("sound/bankmonitor", func_002ADC10);
#ifdef SKIP_ASM
extern "C" void func_002ADC10(void* self)
{
    if (*(int*)((char*)self + 0x94) == 0) {
        *(int*)((char*)self + 0x88) += 1;
    }
}
#endif

INCLUDE_ASM("sound/bankmonitor", func_002ADC30);

INCLUDE_ASM("sound/bankmonitor", func_002ADCA0);

INCLUDE_ASM("sound/bankmonitor", func_002ADDA0);

INCLUDE_ASM("sound/bankmonitor", func_002ADDE0);

INCLUDE_ASM("sound/bankmonitor", func_002ADE88);

INCLUDE_ASM("sound/bankmonitor", func_002ADEE8);

INCLUDE_ASM("sound/bankmonitor", func_002ADF60);

INCLUDE_ASM("sound/bankmonitor", func_002ADF80);

extern void* D_004D3E98[];

//100%
INCLUDE_ASM("sound/bankmonitor", func_002ADFB0__Fi);
#ifdef SKIP_ASM
int func_002ADFB0(int self)
{
    return *(int*)((char*)(void*)D_004D3E98 + self * 4);
}
#endif

extern "C" void* func_002523A8(void* self);

//100%
INCLUDE_ASM("sound/bankmonitor", func_002AE000__FPv);
#ifdef SKIP_ASM
void* func_002AE000(void* self)
{
    return func_002523A8(self);
}
#endif

INCLUDE_ASM("sound/bankmonitor", func_002AE020);

INCLUDE_ASM("sound/bankmonitor", func_002AE048);

INCLUDE_ASM("sound/bankmonitor", func_002AE100);

INCLUDE_ASM("sound/bankmonitor", func_002AE138);

INCLUDE_ASM("sound/bankmonitor", func_002AE188);

INCLUDE_ASM("sound/bankmonitor", func_002AE1B8);

INCLUDE_ASM("sound/bankmonitor", func_002AE1F0);

INCLUDE_ASM("sound/bankmonitor", func_002AE230);

INCLUDE_ASM("sound/bankmonitor", func_002AE298);

INCLUDE_ASM("sound/bankmonitor", func_002AE328);

INCLUDE_ASM("sound/bankmonitor", func_002AE3A8);

INCLUDE_ASM("sound/bankmonitor", func_002AE478);

INCLUDE_ASM("sound/bankmonitor", func_002AE4C0);

INCLUDE_ASM("sound/bankmonitor", func_002AE690);

INCLUDE_ASM("sound/bankmonitor", func_002AE768);

INCLUDE_ASM("sound/bankmonitor", func_002AE7A8);

INCLUDE_ASM("sound/bankmonitor", func_002AE9F8);

INCLUDE_ASM("sound/bankmonitor", func_002AEAA8);

INCLUDE_ASM("sound/bankmonitor", func_002AEBD0);

INCLUDE_ASM("sound/bankmonitor", func_002AEC28);

INCLUDE_ASM("sound/bankmonitor", func_002AEC58);

INCLUDE_ASM("sound/bankmonitor", func_002AEFA8);

INCLUDE_ASM("sound/bankmonitor", func_002AF2F0);

INCLUDE_ASM("sound/bankmonitor", func_002AF370);

INCLUDE_ASM("sound/bankmonitor", func_002AF428);

INCLUDE_ASM("sound/bankmonitor", func_002AF480);

INCLUDE_ASM("sound/bankmonitor", func_002AF4B0);

INCLUDE_ASM("sound/bankmonitor", func_002AF4E0);

INCLUDE_ASM("sound/bankmonitor", func_002AF580);

INCLUDE_ASM("sound/bankmonitor", func_002AF608);

INCLUDE_ASM("sound/bankmonitor", func_002AF6C0);

INCLUDE_ASM("sound/bankmonitor", func_002AF7A0);

INCLUDE_ASM("sound/bankmonitor", func_002AF838);

INCLUDE_ASM("sound/bankmonitor", func_002AF8A8);

//100%
INCLUDE_ASM("sound/bankmonitor", func_002AF8E0__FPv);
#ifdef SKIP_ASM
void* func_002AF8E0(void* self)
{
    int t0 = 0;
    *(int*)((char*)self + 0x48) = t0;
    *(int*)self = -1;
    *(int*)((char*)self + 0x44) = t0;
    *(signed char*)((char*)self + 0x4) = (signed char)t0;
    return self;
}
#endif

INCLUDE_ASM("sound/bankmonitor", func_002AF900);

INCLUDE_ASM("sound/bankmonitor", func_002AF960);

//100%
INCLUDE_ASM("sound/bankmonitor", func_002AFA58);
#ifdef SKIP_ASM
extern "C" int func_002AFA58(void* self, int a1)
{
    return a1 == *(int*)self;
}
#endif

INCLUDE_ASM("sound/bankmonitor", func_002AFA68);

INCLUDE_ASM("sound/bankmonitor", func_002AFB38);

INCLUDE_ASM("sound/bankmonitor", func_002AFC88);

INCLUDE_ASM("sound/bankmonitor", func_002AFD10);

INCLUDE_ASM("sound/bankmonitor", func_002AFD40);

INCLUDE_ASM("sound/bankmonitor", func_002B0088);

INCLUDE_ASM("sound/bankmonitor", func_002B0290);

INCLUDE_ASM("sound/bankmonitor", func_002B0320);

INCLUDE_ASM("sound/bankmonitor", func_002B0348);

INCLUDE_ASM("sound/bankmonitor", func_002B03B8);

INCLUDE_ASM("sound/bankmonitor", func_002B04D8);

INCLUDE_ASM("sound/bankmonitor", func_002B07F8);

INCLUDE_ASM("sound/bankmonitor", func_002B0AE8);

INCLUDE_ASM("sound/bankmonitor", func_002B0C78);

INCLUDE_ASM("sound/bankmonitor", func_002B0CE0);

INCLUDE_ASM("sound/bankmonitor", func_002B0DA0);

INCLUDE_ASM("sound/bankmonitor", func_002B0E28);

INCLUDE_ASM("sound/bankmonitor", func_002B0E60);

INCLUDE_ASM("sound/bankmonitor", func_002B0F48);

INCLUDE_ASM("sound/bankmonitor", func_002B11B0);

INCLUDE_ASM("sound/bankmonitor", func_002B1220);

INCLUDE_ASM("sound/bankmonitor", func_002B1428);

INCLUDE_ASM("sound/bankmonitor", func_002B1458);

INCLUDE_ASM("sound/bankmonitor", func_002B1520);

INCLUDE_ASM("sound/bankmonitor", func_002B1720);

extern "C" void* func_002AFD10(int);

//96.5%
INCLUDE_ASM("sound/bankmonitor", func_002B1758__FPvi);
#ifdef SKIP_ASM
void* func_002B1758(void* self, int a1)
{
    return func_002AFD10(*(int*)((char*)*(void**)((char*)self + 0x4) + a1 * 4));
}
#endif

INCLUDE_ASM("sound/bankmonitor", func_002B1A98);

INCLUDE_ASM("sound/bankmonitor", func_002B1B68);

INCLUDE_ASM("sound/bankmonitor", func_002B1B98);

INCLUDE_ASM("sound/bankmonitor", func_002B1C50);

INCLUDE_ASM("sound/bankmonitor", func_002B1F78);

INCLUDE_ASM("sound/bankmonitor", func_002B2018);

INCLUDE_ASM("sound/bankmonitor", func_002B2070);

INCLUDE_ASM("sound/bankmonitor", func_002B20C8);

extern "C" void func_003D0D70(unsigned int);

//100%
INCLUDE_ASM("sound/bankmonitor", func_002B2120);
#ifdef SKIP_ASM
extern "C" void func_002B2120()
{
    func_003D0D70(0x11000001U);
}
#endif

INCLUDE_ASM("sound/bankmonitor", func_002B2160);

INCLUDE_ASM("sound/bankmonitor", func_002B21E0);

INCLUDE_ASM("sound/bankmonitor", func_002B23E8);

INCLUDE_ASM("sound/bankmonitor", func_002B2418);

INCLUDE_ASM("sound/bankmonitor", func_002B2488);

INCLUDE_ASM("sound/bankmonitor", func_002B24C0);

INCLUDE_ASM("sound/bankmonitor", func_002B2578);

INCLUDE_ASM("sound/bankmonitor", func_002B25C8);

INCLUDE_ASM("sound/bankmonitor", func_002B2600);

INCLUDE_ASM("sound/bankmonitor", func_002B2690);

INCLUDE_ASM("sound/bankmonitor", func_002B2718);

INCLUDE_ASM("sound/bankmonitor", func_002B2850);

INCLUDE_ASM("sound/bankmonitor", func_002B28C0);

INCLUDE_ASM("sound/bankmonitor", func_002B3398);

INCLUDE_ASM("sound/bankmonitor", func_002B35A0);

INCLUDE_ASM("sound/bankmonitor", func_002B3838);

INCLUDE_ASM("sound/bankmonitor", func_002B3A70);

INCLUDE_ASM("sound/bankmonitor", func_002B3A98);

INCLUDE_ASM("sound/bankmonitor", func_002B3AC0);

INCLUDE_ASM("sound/bankmonitor", func_002B3B88);

INCLUDE_ASM("sound/bankmonitor", func_002B3BC0);

INCLUDE_ASM("sound/bankmonitor", func_002B3C28);

INCLUDE_ASM("sound/bankmonitor", func_002B3C98);

//100%
INCLUDE_ASM("sound/bankmonitor", func_002B3CC0);
#ifdef SKIP_ASM
extern "C" void func_002B3CC0(void* self, int a1)
{
    void* p = *(void**)((char*)self + 0x408);
    if (p != 0) {
        *(int*)((char*)p + 0x54) = a1;
    }
}
#endif

INCLUDE_ASM("sound/bankmonitor", func_002B3D10);

INCLUDE_ASM("sound/bankmonitor", func_002B3D48);

INCLUDE_ASM("sound/bankmonitor", func_002B3EB0);

INCLUDE_ASM("sound/bankmonitor", func_002B3EE8);

INCLUDE_ASM("sound/bankmonitor", func_002B3FE8);

//100%
INCLUDE_ASM("sound/bankmonitor", func_002B4060__FPv);
#ifdef SKIP_ASM
void func_002B4060(void* self)
{
}
#endif

INCLUDE_ASM("sound/bankmonitor", func_002B4070);

INCLUDE_ASM("sound/bankmonitor", func_002B40F0);

INCLUDE_ASM("sound/bankmonitor", func_002B4120);

INCLUDE_ASM("sound/bankmonitor", func_002B4150);

INCLUDE_ASM("sound/bankmonitor", func_002B42B8);

INCLUDE_ASM("sound/bankmonitor", func_002B4388);

INCLUDE_ASM("sound/bankmonitor", func_002B43D8);

INCLUDE_ASM("sound/bankmonitor", func_002B4620);

//100%
INCLUDE_ASM("sound/bankmonitor", func_002B46D0);
#ifdef SKIP_ASM
extern "C" void func_002B46D0(void* self)
{
    void* p = *(void**)((char*)self + 0x408);
    if (p != 0) {
        *(int*)((char*)p + 0x50) = 1;
    }
}
#endif

INCLUDE_ASM("sound/bankmonitor", func_002B46E8);

//100%
INCLUDE_ASM("sound/bankmonitor", func_002B4708);
#ifdef SKIP_ASM
extern "C" void func_002B4708(void* self)
{
    void* p = *(void**)((char*)self + 0x408);
    if (p != 0) {
        *(int*)((char*)p + 0x4c) = 0;
    }
}
#endif

//100%
INCLUDE_ASM("sound/bankmonitor", func_002B4868__FPv);
#ifdef SKIP_ASM
int func_002B4868(void* self)
{
    return *(int*)((char*)*(void**)self + 0x94);
}
#endif

INCLUDE_ASM("sound/bankmonitor", func_002B4878);

//96.67%
INCLUDE_ASM("sound/bankmonitor", func_002B4908__FPv);
#ifdef SKIP_ASM
int func_002B4908(void* self)
{
    return *(int*)((char*)*(void**)((char*)((char*)self + *(int*)((char*)self + 0x3f0) * 4) + 0x4) + 0x98);
}
#endif

INCLUDE_ASM("sound/bankmonitor", func_002B4920);

INCLUDE_ASM("sound/bankmonitor", func_002B4978);

//100%
INCLUDE_ASM("sound/bankmonitor", func_002B49C0);
#ifdef SKIP_ASM
extern "C" void func_002B49C0(void* self, int a1)
{
    if (*(int*)((char*)self + 0x418) != 0) {
        void* p = *(void**)((char*)self + 0x408);
        if (p != 0) {
            *(int*)((char*)p + 0x58) = a1;
        }
    }
}
#endif

INCLUDE_ASM("sound/bankmonitor", func_002B49E0);

//100%
INCLUDE_ASM("sound/bankmonitor", func_002B4A08);
#ifdef SKIP_ASM
extern "C" void func_002B4A08(void* self, int a1)
{
    void* p = *(void**)((char*)self + 0x408);
    if (p != 0) {
        *(int*)((char*)p + 0x5c) = a1;
    }
}
#endif

INCLUDE_ASM("sound/bankmonitor", func_002B4A20);

INCLUDE_ASM("sound/bankmonitor", func_002B4AA0);

//100%
INCLUDE_ASM("sound/bankmonitor", func_002B4AE8__FPv);
#ifdef SKIP_ASM
int func_002B4AE8(void* self)
{
    return *(int*)((char*)self + 0x5434);
}
#endif

INCLUDE_ASM("sound/bankmonitor", func_002B4AF0);

