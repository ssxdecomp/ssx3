#include "common.h"

INCLUDE_ASM("fe/feasyncfile", cFEAsyncManager_Load3PeakPic);

INCLUDE_ASM("fe/feasyncfile", cFEAsyncManager_Load1PeakPic);

INCLUDE_ASM("fe/feasyncfile", func_001A37F8);

INCLUDE_ASM("fe/feasyncfile", cFEAsyncManager_UnloadFEAsyncFile);

struct cFEAsyncFileEntry {
    char pad_0x00[0x114];
    int mStatus; // 0x114
    char pad_0x118[0x11C - 0x114 - 4];
};

struct cFEAsyncManager {
    cFEAsyncFileEntry mFiles[1];
};

//100%
INCLUDE_ASM("fe/feasyncfile", cFEAsyncManager_GetFileStatus__FP15cFEAsyncManageri);
#ifdef SKIP_ASM
int cFEAsyncManager_GetFileStatus(cFEAsyncManager* self, int index)
{
    return self->mFiles[index].mStatus;
}
#endif

//100%
INCLUDE_ASM("fe/feasyncfile", cFEAsyncManager_SetFileStatus__FP15cFEAsyncManagerii);
#ifdef SKIP_ASM
void cFEAsyncManager_SetFileStatus(cFEAsyncManager* self, int index, int status)
{
    self->mFiles[index].mStatus = status;
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001A39F0);

INCLUDE_ASM("fe/feasyncfile", func_001A3BF0);

INCLUDE_ASM("fe/feasyncfile", func_001A3C50);

INCLUDE_ASM("fe/feasyncfile", cFEAsyncManager_LoadDataFile);

INCLUDE_ASM("fe/feasyncfile", func_001A3DC8);

INCLUDE_ASM("fe/feasyncfile", func_001A3E30);

INCLUDE_ASM("fe/feasyncfile", func_001A3EA0);

INCLUDE_ASM("fe/feasyncfile", func_001A3F68);

INCLUDE_ASM("fe/feasyncfile", func_001A3FE0);

INCLUDE_ASM("fe/feasyncfile", func_001A4040);

INCLUDE_ASM("fe/feasyncfile", func_001A4170);

INCLUDE_ASM("fe/feasyncfile", func_001A41C0);

INCLUDE_ASM("fe/feasyncfile", func_001A4300);

INCLUDE_ASM("fe/feasyncfile", func_001A4330);

INCLUDE_ASM("fe/feasyncfile", func_001A4670);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001A4740);
#ifdef SKIP_ASM
extern "C" int func_001A4740(void* self, int a1)
{
    return *(int*)((char*)self + 0x6f4) + a1;
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001A4750);

INCLUDE_ASM("fe/feasyncfile", func_001A4810);

INCLUDE_ASM("fe/feasyncfile", func_001A4928);

INCLUDE_ASM("fe/feasyncfile", func_001A49A0);

INCLUDE_ASM("fe/feasyncfile", func_001A4B20);

INCLUDE_ASM("fe/feasyncfile", func_001A4C58);

INCLUDE_ASM("fe/feasyncfile", func_001A4CE8);

INCLUDE_ASM("fe/feasyncfile", func_001A4D90);

INCLUDE_ASM("fe/feasyncfile", func_001A4E28);

INCLUDE_ASM("fe/feasyncfile", func_001A4FB0);

INCLUDE_ASM("fe/feasyncfile", func_001A5010);

INCLUDE_ASM("fe/feasyncfile", func_001A5128);

INCLUDE_ASM("fe/feasyncfile", func_001A52B0);

INCLUDE_ASM("fe/feasyncfile", func_001A5450);

INCLUDE_ASM("fe/feasyncfile", func_001A54D8);

INCLUDE_ASM("fe/feasyncfile", func_001A56D0);

INCLUDE_ASM("fe/feasyncfile", func_001A5800);

INCLUDE_ASM("fe/feasyncfile", func_001A5898);

INCLUDE_ASM("fe/feasyncfile", func_001A5FB8);

INCLUDE_ASM("fe/feasyncfile", func_001A6070);

INCLUDE_ASM("fe/feasyncfile", func_001A63C8);

INCLUDE_ASM("fe/feasyncfile", func_001A6618);

INCLUDE_ASM("fe/feasyncfile", func_001A66A8);

INCLUDE_ASM("fe/feasyncfile", func_001A6978);

INCLUDE_ASM("fe/feasyncfile", func_001A6C40);

INCLUDE_ASM("fe/feasyncfile", func_001A6CA0);

INCLUDE_ASM("fe/feasyncfile", func_001A6E70);

INCLUDE_ASM("fe/feasyncfile", func_001A71B0);

INCLUDE_ASM("fe/feasyncfile", func_001A7390);

INCLUDE_ASM("fe/feasyncfile", func_001A77A0);

INCLUDE_ASM("fe/feasyncfile", func_001A7848);

INCLUDE_ASM("fe/feasyncfile", func_001A7970);

extern "C" void* func_001A8770(void* self);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001A7B20__FPv);
#ifdef SKIP_ASM
void* func_001A7B20(void* self)
{
    return func_001A8770(self);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001A7B40);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001A7BB0__FPv);
#ifdef SKIP_ASM
void func_001A7BB0(void* self)
{
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001A7BB8);

INCLUDE_ASM("fe/feasyncfile", func_001A7D10);

INCLUDE_ASM("fe/feasyncfile", func_001A7D40);

INCLUDE_ASM("fe/feasyncfile", func_001A7D90);

INCLUDE_ASM("fe/feasyncfile", func_001A7DD8);

INCLUDE_ASM("fe/feasyncfile", func_001A7ED8);

INCLUDE_ASM("fe/feasyncfile", func_001A7F78);

INCLUDE_ASM("fe/feasyncfile", func_001A81F0);

INCLUDE_ASM("fe/feasyncfile", func_001A83D8);

INCLUDE_ASM("fe/feasyncfile", func_001A8500);

INCLUDE_ASM("fe/feasyncfile", func_001A85D0);

INCLUDE_ASM("fe/feasyncfile", func_001A86E8);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001A8768__FPv);
#ifdef SKIP_ASM
void func_001A8768(void* self)
{
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001A8770);

INCLUDE_ASM("fe/feasyncfile", func_001A87D0);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001A8828__FPv);
#ifdef SKIP_ASM
int func_001A8828(void* self)
{
    return 0;
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001A8830);

INCLUDE_ASM("fe/feasyncfile", func_001A8918);

INCLUDE_ASM("fe/feasyncfile", func_001A89B0);

INCLUDE_ASM("fe/feasyncfile", func_001A8A40);

INCLUDE_ASM("fe/feasyncfile", func_001A8AE8);

INCLUDE_ASM("fe/feasyncfile", func_001A8B88);

INCLUDE_ASM("fe/feasyncfile", func_001A8E40);

INCLUDE_ASM("fe/feasyncfile", func_001A8F98);

INCLUDE_ASM("fe/feasyncfile", func_001A9090);

INCLUDE_ASM("fe/feasyncfile", func_001A9150);

INCLUDE_ASM("fe/feasyncfile", func_001A91B0);

INCLUDE_ASM("fe/feasyncfile", func_001A9268);

INCLUDE_ASM("fe/feasyncfile", func_001A92D8);

INCLUDE_ASM("fe/feasyncfile", func_001A93D0);

INCLUDE_ASM("fe/feasyncfile", func_001A9438);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001A94D8__FPv);
#ifdef SKIP_ASM
void func_001A94D8(void* self)
{
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001A94E0);

INCLUDE_ASM("fe/feasyncfile", func_001A9578);

INCLUDE_ASM("fe/feasyncfile", func_001A9638);

INCLUDE_ASM("fe/feasyncfile", func_001A9668);

INCLUDE_ASM("fe/feasyncfile", func_001A9710);

INCLUDE_ASM("fe/feasyncfile", func_001A97B8);

INCLUDE_ASM("fe/feasyncfile", func_001A9890);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001A98B0__FPv);
#ifdef SKIP_ASM
int func_001A98B0(void* self)
{
    return *(int*)((char*)self + 0x6C0);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001A98B8);

INCLUDE_ASM("fe/feasyncfile", func_001A9930);

INCLUDE_ASM("fe/feasyncfile", func_001A9A18);

INCLUDE_ASM("fe/feasyncfile", func_001A9AB8);

INCLUDE_ASM("fe/feasyncfile", func_001A9B58);

INCLUDE_ASM("fe/feasyncfile", func_001A9BC0);

INCLUDE_ASM("fe/feasyncfile", func_001A9C50);

INCLUDE_ASM("fe/feasyncfile", func_001A9CC0);

INCLUDE_ASM("fe/feasyncfile", func_001AA9B0);

INCLUDE_ASM("fe/feasyncfile", func_001AAB68);

INCLUDE_ASM("fe/feasyncfile", func_001AAD50);

INCLUDE_ASM("fe/feasyncfile", func_001AAF90);

INCLUDE_ASM("fe/feasyncfile", func_001AB108);

INCLUDE_ASM("fe/feasyncfile", func_001AB178);

INCLUDE_ASM("fe/feasyncfile", func_001AB288);

INCLUDE_ASM("fe/feasyncfile", func_001AB370);

INCLUDE_ASM("fe/feasyncfile", func_001AB3D0);

INCLUDE_ASM("fe/feasyncfile", func_001AB478);

INCLUDE_ASM("fe/feasyncfile", func_001ABB30);

INCLUDE_ASM("fe/feasyncfile", func_001ABC50);

INCLUDE_ASM("fe/feasyncfile", func_001ABCD0);

INCLUDE_ASM("fe/feasyncfile", func_001ABE58);

INCLUDE_ASM("fe/feasyncfile", func_001ABED8);

INCLUDE_ASM("fe/feasyncfile", func_001ABF70);

INCLUDE_ASM("fe/feasyncfile", func_001ABFA8);

INCLUDE_ASM("fe/feasyncfile", func_001AC010);

INCLUDE_ASM("fe/feasyncfile", func_001AC068);

INCLUDE_ASM("fe/feasyncfile", func_001AC0B8);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001AC150__FPv);
#ifdef SKIP_ASM
void* func_001AC150(void* self)
{
    return func_001A8770(self);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001AC170);

INCLUDE_ASM("fe/feasyncfile", func_001AC2B8);

INCLUDE_ASM("fe/feasyncfile", func_001AC360);

INCLUDE_ASM("fe/feasyncfile", func_001AC408);

INCLUDE_ASM("fe/feasyncfile", func_001AC448);

INCLUDE_ASM("fe/feasyncfile", func_001AC4F0);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001AC5A8);
#ifdef SKIP_ASM
extern "C" int func_001AC5A8(void* self, int a1, int a2)
{
    return a2 != 9 ? 0x101 : 0x100;
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001AC5C0);

INCLUDE_ASM("fe/feasyncfile", func_001AC920);

INCLUDE_ASM("fe/feasyncfile", func_001AC9C0);

INCLUDE_ASM("fe/feasyncfile", func_001ACA88);

INCLUDE_ASM("fe/feasyncfile", func_001ACB48);

INCLUDE_ASM("fe/feasyncfile", func_001ACCD0);

INCLUDE_ASM("fe/feasyncfile", func_001ACDD0);

INCLUDE_ASM("fe/feasyncfile", func_001ACEF8);

INCLUDE_ASM("fe/feasyncfile", func_001AD130);

INCLUDE_ASM("fe/feasyncfile", func_001AD178);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001AD1E8__FPv);
#ifdef SKIP_ASM
void* func_001AD1E8(void* self)
{
    return func_001A8770(self);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001AD208);

INCLUDE_ASM("fe/feasyncfile", func_001AD308);

INCLUDE_ASM("fe/feasyncfile", func_001AD3E8);

INCLUDE_ASM("fe/feasyncfile", func_001AD4F0);

INCLUDE_ASM("fe/feasyncfile", func_001AD5E8);

INCLUDE_ASM("fe/feasyncfile", func_001AD8C0);

INCLUDE_ASM("fe/feasyncfile", func_001AD930);

INCLUDE_ASM("fe/feasyncfile", func_001AD9C8);

INCLUDE_ASM("fe/feasyncfile", func_001ADA30);

INCLUDE_ASM("fe/feasyncfile", func_001ADC30);

INCLUDE_ASM("fe/feasyncfile", func_001ADDD0);

INCLUDE_ASM("fe/feasyncfile", func_001ADE88);

INCLUDE_ASM("fe/feasyncfile", func_001ADFB8);

INCLUDE_ASM("fe/feasyncfile", func_001ADFE8);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001AE0E0__FPv);
#ifdef SKIP_ASM
void* func_001AE0E0(void* self)
{
    return func_001A8770(self);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001AE100);

INCLUDE_ASM("fe/feasyncfile", func_001AE128);

INCLUDE_ASM("fe/feasyncfile", func_001AE680);

INCLUDE_ASM("fe/feasyncfile", func_001AE7A0);

INCLUDE_ASM("fe/feasyncfile", func_001AEBF0);

INCLUDE_ASM("fe/feasyncfile", func_001AEC60);

INCLUDE_ASM("fe/feasyncfile", func_001AF098);

INCLUDE_ASM("fe/feasyncfile", func_001AF208);

INCLUDE_ASM("fe/feasyncfile", func_001AF3E0);

INCLUDE_ASM("fe/feasyncfile", func_001AF428);

INCLUDE_ASM("fe/feasyncfile", func_001AF470);

INCLUDE_ASM("fe/feasyncfile", func_001AF568);

INCLUDE_ASM("fe/feasyncfile", func_001AF688);

INCLUDE_ASM("fe/feasyncfile", func_001AF728);

INCLUDE_ASM("fe/feasyncfile", func_001AF930);

INCLUDE_ASM("fe/feasyncfile", func_001AFA60);

INCLUDE_ASM("fe/feasyncfile", func_001AFD88);

INCLUDE_ASM("fe/feasyncfile", func_001AFE08);

INCLUDE_ASM("fe/feasyncfile", func_001AFE68);

INCLUDE_ASM("fe/feasyncfile", func_001B00B8);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001B0130__FPv);
#ifdef SKIP_ASM
void* func_001B0130(void* self)
{
    return func_001A8770(self);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001B0150);

INCLUDE_ASM("fe/feasyncfile", func_001B0538);

INCLUDE_ASM("fe/feasyncfile", func_001B05E0);

INCLUDE_ASM("fe/feasyncfile", func_001B0628);

INCLUDE_ASM("fe/feasyncfile", func_001B0670);

INCLUDE_ASM("fe/feasyncfile", func_001B06E0);

INCLUDE_ASM("fe/feasyncfile", func_001B0708);

INCLUDE_ASM("fe/feasyncfile", func_001B0850);

INCLUDE_ASM("fe/feasyncfile", func_001B0C08);

INCLUDE_ASM("fe/feasyncfile", func_001B0E10);

INCLUDE_ASM("fe/feasyncfile", func_001B0F28);

INCLUDE_ASM("fe/feasyncfile", func_001B0F60);

INCLUDE_ASM("fe/feasyncfile", func_001B0FB0);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001B1048__FPv);
#ifdef SKIP_ASM
void* func_001B1048(void* self)
{
    return func_001A8770(self);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001B1068);

INCLUDE_ASM("fe/feasyncfile", func_001B10F8);

INCLUDE_ASM("fe/feasyncfile", func_001B1280);

INCLUDE_ASM("fe/feasyncfile", func_001B14D8);

INCLUDE_ASM("fe/feasyncfile", func_001B1590);

INCLUDE_ASM("fe/feasyncfile", func_001B15D8);

INCLUDE_ASM("fe/feasyncfile", func_001B1760);

INCLUDE_ASM("fe/feasyncfile", func_001B1808);

INCLUDE_ASM("fe/feasyncfile", func_001B1A08);

INCLUDE_ASM("fe/feasyncfile", func_001B1B10);

INCLUDE_ASM("fe/feasyncfile", func_001B1B98);

INCLUDE_ASM("fe/feasyncfile", func_001B1EC0);

INCLUDE_ASM("fe/feasyncfile", func_001B1F18);

INCLUDE_ASM("fe/feasyncfile", func_001B1F88);

extern void* D_0046AE58[];
extern "C" void* func_001A85D0(void*);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001B2048__FPv);
#ifdef SKIP_ASM
void* func_001B2048(void* self)
{
    *(int*)((char*)self + 0x8) = (int)(void*)D_0046AE58;
    return func_001A85D0(self);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001B2070);

INCLUDE_ASM("fe/feasyncfile", func_001B22A0);

INCLUDE_ASM("fe/feasyncfile", func_001B2320);

INCLUDE_ASM("fe/feasyncfile", func_001B2378);

INCLUDE_ASM("fe/feasyncfile", func_001B25E0);

INCLUDE_ASM("fe/feasyncfile", func_001B27B0);

INCLUDE_ASM("fe/feasyncfile", func_001B2CD0);

INCLUDE_ASM("fe/feasyncfile", func_001B2DA0);

INCLUDE_ASM("fe/feasyncfile", func_001B2EB8);

INCLUDE_ASM("fe/feasyncfile", func_001B31A0);

INCLUDE_ASM("fe/feasyncfile", func_001B33D8);

INCLUDE_ASM("fe/feasyncfile", func_001B3490);

INCLUDE_ASM("fe/feasyncfile", func_001B3528);

INCLUDE_ASM("fe/feasyncfile", func_001B3568);

INCLUDE_ASM("fe/feasyncfile", func_001B35B0);

INCLUDE_ASM("fe/feasyncfile", func_001B3760);

INCLUDE_ASM("fe/feasyncfile", func_001B37D8);

INCLUDE_ASM("fe/feasyncfile", func_001B3850);

INCLUDE_ASM("fe/feasyncfile", func_001B38D0);

INCLUDE_ASM("fe/feasyncfile", func_001B3978);

INCLUDE_ASM("fe/feasyncfile", func_001B3A30);

INCLUDE_ASM("fe/feasyncfile", func_001B3BF0);

INCLUDE_ASM("fe/feasyncfile", func_001B3D20);

INCLUDE_ASM("fe/feasyncfile", func_001B3F78);

INCLUDE_ASM("fe/feasyncfile", func_001B4018);

INCLUDE_ASM("fe/feasyncfile", func_001B40D0);

INCLUDE_ASM("fe/feasyncfile", func_001B4168);

//63.33%
INCLUDE_ASM("fe/feasyncfile", func_001B4198__FPv);
#ifdef SKIP_ASM
int func_001B4198(void* self)
{
    int t0 = 6;
    *(int*)((char*)self + 0x708) = t0;
    return t0;
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001B41A8);

INCLUDE_ASM("fe/feasyncfile", func_001B43A8);

INCLUDE_ASM("fe/feasyncfile", func_001B4470);

INCLUDE_ASM("fe/feasyncfile", func_001B45E8);

INCLUDE_ASM("fe/feasyncfile", func_001B47C0);

INCLUDE_ASM("fe/feasyncfile", func_001B4888);

INCLUDE_ASM("fe/feasyncfile", func_001B4C00);

INCLUDE_ASM("fe/feasyncfile", func_001B4C40);

INCLUDE_ASM("fe/feasyncfile", func_001B4CD8);

INCLUDE_ASM("fe/feasyncfile", func_001B4FA0);

INCLUDE_ASM("fe/feasyncfile", func_001B5068);

INCLUDE_ASM("fe/feasyncfile", func_001B5268);

INCLUDE_ASM("fe/feasyncfile", func_001B52C8);

INCLUDE_ASM("fe/feasyncfile", func_001B54B8);

INCLUDE_ASM("fe/feasyncfile", func_001B55B0);

INCLUDE_ASM("fe/feasyncfile", func_001B5740);

INCLUDE_ASM("fe/feasyncfile", func_001B5830);

INCLUDE_ASM("fe/feasyncfile", func_001B5A58);

INCLUDE_ASM("fe/feasyncfile", func_001B5BD8);

INCLUDE_ASM("fe/feasyncfile", func_001B5CF8);

INCLUDE_ASM("fe/feasyncfile", func_001B5D58);

INCLUDE_ASM("fe/feasyncfile", func_001B5E28);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001B6078__FPv);
#ifdef SKIP_ASM
int func_001B6078(void* self)
{
    return 0x101;
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001B6080);

INCLUDE_ASM("fe/feasyncfile", func_001B60A8);

INCLUDE_ASM("fe/feasyncfile", func_001B6288);

INCLUDE_ASM("fe/feasyncfile", func_001B6368);

INCLUDE_ASM("fe/feasyncfile", func_001B63E8);

INCLUDE_ASM("fe/feasyncfile", func_001B65C0);

INCLUDE_ASM("fe/feasyncfile", func_001B66B8);

INCLUDE_ASM("fe/feasyncfile", func_001B6740);

INCLUDE_ASM("fe/feasyncfile", func_001B6770);

INCLUDE_ASM("fe/feasyncfile", func_001B6798);

INCLUDE_ASM("fe/feasyncfile", func_001B6A90);

INCLUDE_ASM("fe/feasyncfile", func_001B6AB8);

extern void* D_004688E0[];
extern "C" void* func_001A85D0(void*);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001B6B28__FPv);
#ifdef SKIP_ASM
void* func_001B6B28(void* self)
{
    *(int*)((char*)self + 0x8) = (int)(void*)D_004688E0;
    return func_001A85D0(self);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001B6B50);

INCLUDE_ASM("fe/feasyncfile", func_001B6BB8);

INCLUDE_ASM("fe/feasyncfile", func_001B6C98);

INCLUDE_ASM("fe/feasyncfile", func_001B6E10);

INCLUDE_ASM("fe/feasyncfile", func_001B6E40);

INCLUDE_ASM("fe/feasyncfile", func_001B6EA8);

INCLUDE_ASM("fe/feasyncfile", func_001B6ED0);

INCLUDE_ASM("fe/feasyncfile", func_001B7030);

extern "C" void* func_001ABFA8(void* self);

//99.29%
INCLUDE_ASM("fe/feasyncfile", func_001B7088__FPv);
#ifdef SKIP_ASM
void* func_001B7088(void* self)
{
    return func_001ABFA8(self);
}
#endif

extern "C" void* func_001B7778(void*);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001B70A8__FPv);
#ifdef SKIP_ASM
void* func_001B70A8(void* self)
{
    int t0 = 0;
    *(signed char*)((char*)self + 0x6e0) = (signed char)t0;
    *(signed char*)((char*)self + 0x6f1) = (signed char)t0;
    return func_001B7778(self);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001B70D0);

INCLUDE_ASM("fe/feasyncfile", func_001B7650);

INCLUDE_ASM("fe/feasyncfile", func_001B7778);

extern "C" void* func_001B70D0(void*, int);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001B77A8__FPv);
#ifdef SKIP_ASM
void* func_001B77A8(void* self)
{
    return func_001B70D0(self, 2);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001B77C8);

INCLUDE_ASM("fe/feasyncfile", func_001B7820);

INCLUDE_ASM("fe/feasyncfile", func_001B78F0);

INCLUDE_ASM("fe/feasyncfile", func_001B7938);

INCLUDE_ASM("fe/feasyncfile", func_001B7A08);

INCLUDE_ASM("fe/feasyncfile", func_001B7A50);

INCLUDE_ASM("fe/feasyncfile", func_001B7A98);

INCLUDE_ASM("fe/feasyncfile", func_001B7BC0);

INCLUDE_ASM("fe/feasyncfile", func_001B7C28);

INCLUDE_ASM("fe/feasyncfile", func_001B7C70);

INCLUDE_ASM("fe/feasyncfile", func_001B7CB8);

INCLUDE_ASM("fe/feasyncfile", func_001B7E40);

INCLUDE_ASM("fe/feasyncfile", func_001B8238);

INCLUDE_ASM("fe/feasyncfile", func_001B83C0);

INCLUDE_ASM("fe/feasyncfile", func_001B84D8);

INCLUDE_ASM("fe/feasyncfile", func_001B8860);

INCLUDE_ASM("fe/feasyncfile", func_001B8890);

INCLUDE_ASM("fe/feasyncfile", func_001B88F0);

INCLUDE_ASM("fe/feasyncfile", func_001B8960);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001B89E8__FPv);
#ifdef SKIP_ASM
void* func_001B89E8(void* self)
{
    return func_001A8770(self);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001B8A08);

INCLUDE_ASM("fe/feasyncfile", func_001B8AA0);

INCLUDE_ASM("fe/feasyncfile", func_001B8C38);

INCLUDE_ASM("fe/feasyncfile", func_001B9088);

INCLUDE_ASM("fe/feasyncfile", func_001B91C8);

INCLUDE_ASM("fe/feasyncfile", func_001B92C8);

INCLUDE_ASM("fe/feasyncfile", func_001B9428);

INCLUDE_ASM("fe/feasyncfile", func_001B9488);

INCLUDE_ASM("fe/feasyncfile", func_001B9558);

INCLUDE_ASM("fe/feasyncfile", func_001B95C0);

INCLUDE_ASM("fe/feasyncfile", func_001B9610);

INCLUDE_ASM("fe/feasyncfile", func_001B9678);

INCLUDE_ASM("fe/feasyncfile", func_001B96E0);

INCLUDE_ASM("fe/feasyncfile", func_001B9740);

INCLUDE_ASM("fe/feasyncfile", func_001B97B0);

INCLUDE_ASM("fe/feasyncfile", func_001B9820);

INCLUDE_ASM("fe/feasyncfile", func_001B9950);

INCLUDE_ASM("fe/feasyncfile", func_001B9B18);

INCLUDE_ASM("fe/feasyncfile", func_001B9CD8);

INCLUDE_ASM("fe/feasyncfile", func_001B9D68);

INCLUDE_ASM("fe/feasyncfile", func_001B9F68);

INCLUDE_ASM("fe/feasyncfile", func_001B9FA0);

INCLUDE_ASM("fe/feasyncfile", func_001BA110);

INCLUDE_ASM("fe/feasyncfile", func_001BA178);

INCLUDE_ASM("fe/feasyncfile", func_001BA218);

INCLUDE_ASM("fe/feasyncfile", func_001BA280);

INCLUDE_ASM("fe/feasyncfile", func_001BA358);

INCLUDE_ASM("fe/feasyncfile", func_001BA3E0);

INCLUDE_ASM("fe/feasyncfile", func_001BA428);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001BA4E0__FPv);
#ifdef SKIP_ASM
void* func_001BA4E0(void* self)
{
    return func_001A8770(self);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001BA500);

INCLUDE_ASM("fe/feasyncfile", func_001BA618);

INCLUDE_ASM("fe/feasyncfile", func_001BA8B8);

INCLUDE_ASM("fe/feasyncfile", func_001BA9F8);

INCLUDE_ASM("fe/feasyncfile", func_001BAA88);

INCLUDE_ASM("fe/feasyncfile", func_001BAB28);

INCLUDE_ASM("fe/feasyncfile", func_001BAC90);

INCLUDE_ASM("fe/feasyncfile", func_001BADE8);

INCLUDE_ASM("fe/feasyncfile", func_001BAED8);

INCLUDE_ASM("fe/feasyncfile", func_001BB098);

INCLUDE_ASM("fe/feasyncfile", func_001BB0E8);

INCLUDE_ASM("fe/feasyncfile", func_001BB158);

INCLUDE_ASM("fe/feasyncfile", func_001BB2D0);

INCLUDE_ASM("fe/feasyncfile", func_001BB340);

INCLUDE_ASM("fe/feasyncfile", func_001BB3B0);

INCLUDE_ASM("fe/feasyncfile", func_001BB440);

INCLUDE_ASM("fe/feasyncfile", func_001BB4B0);

INCLUDE_ASM("fe/feasyncfile", func_001BB520);

INCLUDE_ASM("fe/feasyncfile", func_001BB5D0);

INCLUDE_ASM("fe/feasyncfile", func_001BB798);

INCLUDE_ASM("fe/feasyncfile", func_001BB840);

INCLUDE_ASM("fe/feasyncfile", func_001BB968);

INCLUDE_ASM("fe/feasyncfile", func_001BB9B0);

extern "C" void* func_001BBC40(void* self);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001BBAA8__FPv);
#ifdef SKIP_ASM
int func_001BBAA8(void* self)
{
    return (func_001BBC40(self) != 0);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001BBAC8);

INCLUDE_ASM("fe/feasyncfile", func_001BBC40);

INCLUDE_ASM("fe/feasyncfile", func_001BBD08);

INCLUDE_ASM("fe/feasyncfile", func_001BBD60);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001BBDE0__FPv);
#ifdef SKIP_ASM
void* func_001BBDE0(void* self)
{
    return func_001A8770(self);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001BBE00);

INCLUDE_ASM("fe/feasyncfile", func_001BBF18);

INCLUDE_ASM("fe/feasyncfile", func_001BC190);

INCLUDE_ASM("fe/feasyncfile", func_001BC290);

INCLUDE_ASM("fe/feasyncfile", func_001BC300);

INCLUDE_ASM("fe/feasyncfile", func_001BC400);

INCLUDE_ASM("fe/feasyncfile", func_001BC4F0);

INCLUDE_ASM("fe/feasyncfile", func_001BC6A0);

INCLUDE_ASM("fe/feasyncfile", func_001BC728);

INCLUDE_ASM("fe/feasyncfile", func_001BC818);

INCLUDE_ASM("fe/feasyncfile", func_001BC990);

INCLUDE_ASM("fe/feasyncfile", func_001BCB58);

INCLUDE_ASM("fe/feasyncfile", func_001BCC30);

INCLUDE_ASM("fe/feasyncfile", func_001BCCA8);

INCLUDE_ASM("fe/feasyncfile", func_001BCD18);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001BCE18__FPv);
#ifdef SKIP_ASM
void* func_001BCE18(void* self)
{
    return func_001A8770(self);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001BCE38);

INCLUDE_ASM("fe/feasyncfile", func_001BD1B8);

INCLUDE_ASM("fe/feasyncfile", func_001BD428);

INCLUDE_ASM("fe/feasyncfile", func_001BD460);

INCLUDE_ASM("fe/feasyncfile", func_001BD540);

INCLUDE_ASM("fe/feasyncfile", func_001BD610);

INCLUDE_ASM("fe/feasyncfile", func_001BD738);

INCLUDE_ASM("fe/feasyncfile", func_001BD848);

INCLUDE_ASM("fe/feasyncfile", func_001BD8C8);

INCLUDE_ASM("fe/feasyncfile", func_001BDA88);

INCLUDE_ASM("fe/feasyncfile", func_001BDC18);

INCLUDE_ASM("fe/feasyncfile", func_001BDCA0);

INCLUDE_ASM("fe/feasyncfile", func_001BDCF8);

INCLUDE_ASM("fe/feasyncfile", func_001BDD60);

INCLUDE_ASM("fe/feasyncfile", func_001BDDE8);

INCLUDE_ASM("fe/feasyncfile", func_001BDE48);

INCLUDE_ASM("fe/feasyncfile", func_001BDF60);

INCLUDE_ASM("fe/feasyncfile", func_001BDFD8);

INCLUDE_ASM("fe/feasyncfile", func_001BE038);

INCLUDE_ASM("fe/feasyncfile", func_001BE0A8);

INCLUDE_ASM("fe/feasyncfile", func_001BE3A8);

INCLUDE_ASM("fe/feasyncfile", func_001BE510);

INCLUDE_ASM("fe/feasyncfile", func_001BE540);

INCLUDE_ASM("fe/feasyncfile", func_001BE720);

INCLUDE_ASM("fe/feasyncfile", func_001BE7D8);

INCLUDE_ASM("fe/feasyncfile", func_001BE828);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001BE890__FPv);
#ifdef SKIP_ASM
void* func_001BE890(void* self)
{
    return func_001A8770(self);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001BE8B0);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001BEA30__FPv);
#ifdef SKIP_ASM
int func_001BEA30(void* self)
{
    return 0x101;
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001BEA38);

INCLUDE_ASM("fe/feasyncfile", func_001BEC78);

INCLUDE_ASM("fe/feasyncfile", func_001BED28);

INCLUDE_ASM("fe/feasyncfile", func_001BED58);

INCLUDE_ASM("fe/feasyncfile", func_001BEE30);

INCLUDE_ASM("fe/feasyncfile", func_001BEE78);

INCLUDE_ASM("fe/feasyncfile", func_001BEED0);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001BEF40__FPv);
#ifdef SKIP_ASM
void* func_001BEF40(void* self)
{
    return func_001A8770(self);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001BEF60);

INCLUDE_ASM("fe/feasyncfile", func_001BF228);

INCLUDE_ASM("fe/feasyncfile", func_001BF378);

INCLUDE_ASM("fe/feasyncfile", func_001BF438);

INCLUDE_ASM("fe/feasyncfile", func_001BF5A8);

INCLUDE_ASM("fe/feasyncfile", func_001BF6C0);

INCLUDE_ASM("fe/feasyncfile", func_001BF758);

INCLUDE_ASM("fe/feasyncfile", func_001BFAE0);

INCLUDE_ASM("fe/feasyncfile", func_001BFBB8);

INCLUDE_ASM("fe/feasyncfile", func_001BFBF8);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001BFCA0__FPv);
#ifdef SKIP_ASM
void* func_001BFCA0(void* self)
{
    return func_001A8770(self);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001BFCC0);

INCLUDE_ASM("fe/feasyncfile", func_001BFD98);

INCLUDE_ASM("fe/feasyncfile", func_001BFE70);

INCLUDE_ASM("fe/feasyncfile", func_001C0138);

INCLUDE_ASM("fe/feasyncfile", func_001C0240);

INCLUDE_ASM("fe/feasyncfile", func_001C02F8);

INCLUDE_ASM("fe/feasyncfile", func_001C0358);

INCLUDE_ASM("fe/feasyncfile", func_001C0418);

INCLUDE_ASM("fe/feasyncfile", func_001C04A8);

INCLUDE_ASM("fe/feasyncfile", func_001C0540);

INCLUDE_ASM("fe/feasyncfile", func_001C0A28);

INCLUDE_ASM("fe/feasyncfile", func_001C0A80);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001C0B08);
#ifdef SKIP_ASM
extern "C" int func_001C0B08(void* self, int a1, int a2)
{
    return a2 != 9 ? 0x101 : 0x100;
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001C0B20);

INCLUDE_ASM("fe/feasyncfile", func_001C0CE0);

INCLUDE_ASM("fe/feasyncfile", func_001C0D28);

extern "C" void* func_001A8E40(void* self);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001C0E88__FPv);
#ifdef SKIP_ASM
void* func_001C0E88(void* self)
{
    return func_001A8E40(self);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001C0EA8);

INCLUDE_ASM("fe/feasyncfile", func_001C0F40);

INCLUDE_ASM("fe/feasyncfile", func_001C0FC0);

INCLUDE_ASM("fe/feasyncfile", func_001C1038);

INCLUDE_ASM("fe/feasyncfile", func_001C1080);

INCLUDE_ASM("fe/feasyncfile", func_001C13E0);

INCLUDE_ASM("fe/feasyncfile", func_001C1488);

INCLUDE_ASM("fe/feasyncfile", func_001C1560);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001C17D8__FPv);
#ifdef SKIP_ASM
int func_001C17D8(void* self)
{
    return 0x101;
}
#endif

//100%
INCLUDE_ASM("fe/feasyncfile", func_001C17E0);
#ifdef SKIP_ASM
extern "C" int func_001C17E0(void* self, int a1, int a2)
{
    return a2 != 9 ? 0x101 : 0x100;
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001C17F8);

INCLUDE_ASM("fe/feasyncfile", func_001C19C8);

INCLUDE_ASM("fe/feasyncfile", func_001C1B48);

INCLUDE_ASM("fe/feasyncfile", func_001C1B88);

INCLUDE_ASM("fe/feasyncfile", func_001C1C50);

INCLUDE_ASM("fe/feasyncfile", func_001C1C90);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001C1D10__FPv);
#ifdef SKIP_ASM
void* func_001C1D10(void* self)
{
    return func_001A8770(self);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001C1D30);

INCLUDE_ASM("fe/feasyncfile", func_001C1E08);

INCLUDE_ASM("fe/feasyncfile", func_001C1EA8);

INCLUDE_ASM("fe/feasyncfile", func_001C20F8);

INCLUDE_ASM("fe/feasyncfile", func_001C2138);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001C21A0__FPv);
#ifdef SKIP_ASM
void* func_001C21A0(void* self)
{
    return func_001A8770(self);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001C21C0);

INCLUDE_ASM("fe/feasyncfile", func_001C2298);

INCLUDE_ASM("fe/feasyncfile", func_001C23C0);

INCLUDE_ASM("fe/feasyncfile", func_001C2418);

INCLUDE_ASM("fe/feasyncfile", func_001C2468);

INCLUDE_ASM("fe/feasyncfile", func_001C2578);

INCLUDE_ASM("fe/feasyncfile", func_001C2740);

INCLUDE_ASM("fe/feasyncfile", func_001C2A18);

INCLUDE_ASM("fe/feasyncfile", func_001C2B48);

INCLUDE_ASM("fe/feasyncfile", func_001C2BA8);

INCLUDE_ASM("fe/feasyncfile", func_001C2C50);

INCLUDE_ASM("fe/feasyncfile", func_001C2D18);

INCLUDE_ASM("fe/feasyncfile", func_001C2E00);

INCLUDE_ASM("fe/feasyncfile", func_001C2E70);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001C2EE0__FPv);
#ifdef SKIP_ASM
void* func_001C2EE0(void* self)
{
    return func_001A8770(self);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001C2F00);

INCLUDE_ASM("fe/feasyncfile", func_001C32B8);

INCLUDE_ASM("fe/feasyncfile", func_001C3310);

INCLUDE_ASM("fe/feasyncfile", func_001C3570);

INCLUDE_ASM("fe/feasyncfile", func_001C3668);

INCLUDE_ASM("fe/feasyncfile", func_001C3D68);

INCLUDE_ASM("fe/feasyncfile", func_001C3EE8);

INCLUDE_ASM("fe/feasyncfile", func_001C4538);

INCLUDE_ASM("fe/feasyncfile", func_001C47A8);

INCLUDE_ASM("fe/feasyncfile", func_001C49C8);

INCLUDE_ASM("fe/feasyncfile", func_001C4B78);

INCLUDE_ASM("fe/feasyncfile", func_001C4B98);

INCLUDE_ASM("fe/feasyncfile", func_001C4BD8);

INCLUDE_ASM("fe/feasyncfile", func_001C4CD8);

INCLUDE_ASM("fe/feasyncfile", func_001C4D28);

INCLUDE_ASM("fe/feasyncfile", func_001C4E40);

INCLUDE_ASM("fe/feasyncfile", func_001C4F58);

INCLUDE_ASM("fe/feasyncfile", func_001C5018);

INCLUDE_ASM("fe/feasyncfile", func_001C5098);

INCLUDE_ASM("fe/feasyncfile", func_001C5108);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001C5178__FPv);
#ifdef SKIP_ASM
void* func_001C5178(void* self)
{
    return func_001A8770(self);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001C5198);

INCLUDE_ASM("fe/feasyncfile", func_001C5310);

INCLUDE_ASM("fe/feasyncfile", func_001C5368);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001C5420);
#ifdef SKIP_ASM
extern "C" int func_001C5420(void* self, void* a1, int a2)
{
    return a2 == 4 ? 0 : 0x101;
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001C5430);

INCLUDE_ASM("fe/feasyncfile", func_001C5540);

INCLUDE_ASM("fe/feasyncfile", func_001C55F8);

INCLUDE_ASM("fe/feasyncfile", func_001C5630);

INCLUDE_ASM("fe/feasyncfile", func_001C5750);

//85.43%
INCLUDE_ASM("fe/feasyncfile", func_001C5780__FPvii);
#ifdef SKIP_ASM
int func_001C5780(void* self, int a1, int a2)
{
    int t0 = 2;
    *(int*)((char*)((char*)self + a1 * 8) + 0x28) = a2;
    *(int*)((char*)((char*)self + a1 * 8) + 0x24) = t0;
    return t0;
}
#endif

//85.43%
INCLUDE_ASM("fe/feasyncfile", func_001C57A0__FPvii);
#ifdef SKIP_ASM
int func_001C57A0(void* self, int a1, int a2)
{
    int t0 = 1;
    *(int*)((char*)((char*)self + a1 * 8) + 0x28) = a2;
    *(int*)((char*)((char*)self + a1 * 8) + 0x24) = t0;
    return t0;
}
#endif

//85.43%
INCLUDE_ASM("fe/feasyncfile", func_001C57C0__FPvii);
#ifdef SKIP_ASM
int func_001C57C0(void* self, int a1, int a2)
{
    int t0 = 3;
    *(int*)((char*)((char*)self + a1 * 8) + 0x28) = a2;
    *(int*)((char*)((char*)self + a1 * 8) + 0x24) = t0;
    return t0;
}
#endif

//100%
INCLUDE_ASM("fe/feasyncfile", func_001C5800);
#ifdef SKIP_ASM
extern "C" void* func_001C5800(void* self, int a1)
{
    return (char*)self + ((a1 << 3) + 0x24);
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001C5838);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001C5860);
#ifdef SKIP_ASM
extern "C" void func_001C5860(void* self, int a1)
{
    char* p = (char*)self + a1 * 0xc;
    *(int*)(p + 0x54) = 0;
}
#endif

INCLUDE_ASM("fe/feasyncfile", func_001C5878);

//100%
INCLUDE_ASM("fe/feasyncfile", func_001C58D0);
#ifdef SKIP_ASM
extern "C" void* func_001C58D0(void* self, int a1)
{
    return (char*)self + (a1 * 0xc + 0x54);
}
#endif

