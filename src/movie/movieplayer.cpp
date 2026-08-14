#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* func_00242288(void* self);
extern const char D_0047C128[];
extern void* D_004A2C74;

//99.53%
INCLUDE_ASM("movie/movieplayer", cMCOverlayManager_getManager__Fv);
#ifdef SKIP_ASM
void* cMCOverlayManager_getManager()
{
    if (D_004A2C74 == 0) {
        void* mem = cMemMan_alloc(0x74C, D_0047C128, 0, 0);
        D_004A2C74 = func_00242288(mem);
    }
    return D_004A2C74;
}
#endif

INCLUDE_ASM("movie/movieplayer", func_0023C860);

//100%
INCLUDE_ASM("movie/movieplayer", func_0023C898);
#ifdef SKIP_ASM
extern "C" int func_0023C898(void* self)
{
    return *(int*)((char*)self + 0x130) == 1;
}
#endif

//100%
INCLUDE_ASM("movie/movieplayer", func_0023C8D0);
#ifdef SKIP_ASM
extern "C" int func_0023C8D0(void* self)
{
    // masks applied as separate statements; folding them into one
    // expression collapses the two `and` instructions into one
    int v = *(int*)((char*)self + 0x43c);
    v &= -5;
    v &= -481;
    return v != 0;
}
#endif

INCLUDE_ASM("movie/movieplayer", func_0023C8F0);

INCLUDE_ASM("movie/movieplayer", func_0023CA28);

INCLUDE_ASM("movie/movieplayer", func_0023CA70);

INCLUDE_ASM("movie/movieplayer", func_0023CAA0);

INCLUDE_ASM("movie/movieplayer", func_0023CAE8);

INCLUDE_ASM("movie/movieplayer", func_0023CC20);

extern "C" void* func_0023CAA0(void* self);

//99.29%
INCLUDE_ASM("movie/movieplayer", func_0023CC58__FPv);
#ifdef SKIP_ASM
void* func_0023CC58(void* self)
{
    return func_0023CAA0(self);
}
#endif

INCLUDE_ASM("movie/movieplayer", func_0023CC78);

INCLUDE_ASM("movie/movieplayer", cMCOverlayManager_setTitleString);

INCLUDE_ASM("movie/movieplayer", func_0023CF38);

INCLUDE_ASM("movie/movieplayer", func_0023D570);

INCLUDE_ASM("movie/movieplayer", func_0023D5A8);

INCLUDE_ASM("movie/movieplayer", func_0023D5E8);

INCLUDE_ASM("movie/movieplayer", func_0023D618);

INCLUDE_ASM("movie/movieplayer", func_0023D660);

INCLUDE_ASM("movie/movieplayer", func_0023D7D8);

INCLUDE_ASM("movie/movieplayer", func_0023E268);

//100%
INCLUDE_ASM("movie/movieplayer", func_0023E2C0__FPv);
#ifdef SKIP_ASM
void func_0023E2C0(void* self)
{
}
#endif

INCLUDE_ASM("movie/movieplayer", func_0023E2C8);

INCLUDE_ASM("movie/movieplayer", func_0023E320);

INCLUDE_ASM("movie/movieplayer", func_0023E3C0);

INCLUDE_ASM("movie/movieplayer", func_0023E428);

INCLUDE_ASM("movie/movieplayer", func_0023E498);

//100%
INCLUDE_ASM("movie/movieplayer", func_0023E4F0__FPv);
#ifdef SKIP_ASM
void func_0023E4F0(void* self)
{
}
#endif

INCLUDE_ASM("movie/movieplayer", func_0023E4F8);

INCLUDE_ASM("movie/movieplayer", func_0023E540);

INCLUDE_ASM("movie/movieplayer", func_0023E820);

INCLUDE_ASM("movie/movieplayer", func_0023EA30);

INCLUDE_ASM("movie/movieplayer", func_0023EA90);

INCLUDE_ASM("movie/movieplayer", func_0023EB50);

INCLUDE_ASM("movie/movieplayer", func_0023EB80);

INCLUDE_ASM("movie/movieplayer", func_0023EC00);

INCLUDE_ASM("movie/movieplayer", func_0023EF68);

INCLUDE_ASM("movie/movieplayer", func_0023F050);

INCLUDE_ASM("movie/movieplayer", func_0023F0F8);

INCLUDE_ASM("movie/movieplayer", func_0023F150);

INCLUDE_ASM("movie/movieplayer", func_0023F1D8);

INCLUDE_ASM("movie/movieplayer", func_0023F258);

INCLUDE_ASM("movie/movieplayer", func_0023F2D8);

INCLUDE_ASM("movie/movieplayer", func_0023F308);

INCLUDE_ASM("movie/movieplayer", func_0023F3A0);

INCLUDE_ASM("movie/movieplayer", func_0023F438);

INCLUDE_ASM("movie/movieplayer", func_0023F4F8);

INCLUDE_ASM("movie/movieplayer", func_0023F578);

INCLUDE_ASM("movie/movieplayer", func_0023F698);

INCLUDE_ASM("movie/movieplayer", func_0023FAE0);

//100%
INCLUDE_ASM("movie/movieplayer", func_0023FB18__FPvi);
#ifdef SKIP_ASM
void func_0023FB18(void* self, int val)
{
    *(int*)((char*)self + 0x428) = val;
}
#endif

INCLUDE_ASM("movie/movieplayer", func_0023FB20);

INCLUDE_ASM("movie/movieplayer", func_0023FB58);

INCLUDE_ASM("movie/movieplayer", func_0023FBB8);

INCLUDE_ASM("movie/movieplayer", func_0023FC70);

INCLUDE_ASM("movie/movieplayer", func_0023FD08);

INCLUDE_ASM("movie/movieplayer", func_0023FD40);

INCLUDE_ASM("movie/movieplayer", func_0023FE70);

INCLUDE_ASM("movie/movieplayer", func_0023FF00);

INCLUDE_ASM("movie/movieplayer", func_0023FFC0);

INCLUDE_ASM("movie/movieplayer", func_0023FFF0);

INCLUDE_ASM("movie/movieplayer", func_002400B0);

INCLUDE_ASM("movie/movieplayer", func_00240130);

INCLUDE_ASM("movie/movieplayer", func_002402D0);

INCLUDE_ASM("movie/movieplayer", func_002405D0);

INCLUDE_ASM("movie/movieplayer", func_00240688);

INCLUDE_ASM("movie/movieplayer", func_00240768);

INCLUDE_ASM("movie/movieplayer", func_00240800);

INCLUDE_ASM("movie/movieplayer", func_00240860);

INCLUDE_ASM("movie/movieplayer", func_00240960);

INCLUDE_ASM("movie/movieplayer", func_002409C8);

INCLUDE_ASM("movie/movieplayer", func_00240AB0);

INCLUDE_ASM("movie/movieplayer", func_00240B88);

INCLUDE_ASM("movie/movieplayer", func_00240C30);

INCLUDE_ASM("movie/movieplayer", func_00240C90);

INCLUDE_ASM("movie/movieplayer", func_00240CC0);

INCLUDE_ASM("movie/movieplayer", func_00240D90);

INCLUDE_ASM("movie/movieplayer", func_00240EB0);

INCLUDE_ASM("movie/movieplayer", func_00240EE0);

extern "C" void* func_0023FB58(void* self);

//99.29%
INCLUDE_ASM("movie/movieplayer", func_00240F10__FPv);
#ifdef SKIP_ASM
void* func_00240F10(void* self)
{
    return func_0023FB58(self);
}
#endif

INCLUDE_ASM("movie/movieplayer", func_00240F30);

INCLUDE_ASM("movie/movieplayer", func_00241000);

INCLUDE_ASM("movie/movieplayer", func_002410A0);

INCLUDE_ASM("movie/movieplayer", func_00241138);

INCLUDE_ASM("movie/movieplayer", func_00241180);

INCLUDE_ASM("movie/movieplayer", func_00241200);

INCLUDE_ASM("movie/movieplayer", func_00241240);

INCLUDE_ASM("movie/movieplayer", func_002412A0);

INCLUDE_ASM("movie/movieplayer", func_00241380);

INCLUDE_ASM("movie/movieplayer", func_00241400);

INCLUDE_ASM("movie/movieplayer", func_00241540);

INCLUDE_ASM("movie/movieplayer", cMCOverlayManager_GetDeviceDisplayString);

//100%
INCLUDE_ASM("movie/movieplayer", func_002419D8);
#ifdef SKIP_ASM
extern "C" int func_002419D8(void* self, int a1)
{
    char* p = (char*)self + a1 * 0xe0;
    return *(int*)(p + 0x354);
}
#endif

INCLUDE_ASM("movie/movieplayer", cMCOverlayManager_GetDeviceTotalString);

struct sPad16 { char x; int pad[3]; };
extern sPad16 D_0047C3A8;
extern "C" void func_002C2540(void*, void*);

//100%
INCLUDE_ASM("movie/movieplayer", func_00241AA0);
#ifdef SKIP_ASM
extern "C" void func_00241AA0(void* self)
{
    func_002C2540(self, &D_0047C3A8);
}
#endif

INCLUDE_ASM("movie/movieplayer", func_00241AC0);

INCLUDE_ASM("movie/movieplayer", func_00241B20);

INCLUDE_ASM("movie/movieplayer", func_00241CD8);

INCLUDE_ASM("movie/movieplayer", func_00241D40);

INCLUDE_ASM("movie/movieplayer", func_00241DC8);

INCLUDE_ASM("movie/movieplayer", func_00241E18);

extern "C" void* func_002420C8(void*, int);

//100%
INCLUDE_ASM("movie/movieplayer", func_00241FB0__FPv);
#ifdef SKIP_ASM
void* func_00241FB0(void* self)
{
    return func_002420C8(self, *(int*)((char*)self + 0x42c));
}
#endif

INCLUDE_ASM("movie/movieplayer", func_00241FD0);

INCLUDE_ASM("movie/movieplayer", func_00242050);

INCLUDE_ASM("movie/movieplayer", func_002420C8);

INCLUDE_ASM("movie/movieplayer", func_00242288);

INCLUDE_ASM("movie/movieplayer", func_002424C8);

//100%
INCLUDE_ASM("movie/movieplayer", func_00242500__FPv);
#ifdef SKIP_ASM
void* func_00242500(void* self)
{
    int t0 = 0;
    *(int*)((char*)self + 0x4) = t0;
    *(int*)((char*)self + 0x108) = t0;
    *(int*)((char*)self + 0x10c) = t0;
    *(int*)self = t0;
    return self;
}
#endif

INCLUDE_ASM("movie/movieplayer", func_00242518);

INCLUDE_ASM("movie/movieplayer", func_00242540);

INCLUDE_ASM("movie/movieplayer", func_00242570);

INCLUDE_ASM("movie/movieplayer", func_002425C0);

INCLUDE_ASM("movie/movieplayer", func_00242978);

INCLUDE_ASM("movie/movieplayer", func_002429B0);

