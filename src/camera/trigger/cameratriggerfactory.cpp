#include "common.h"

INCLUDE_ASM("camera/trigger/cameratriggerfactory", get_camaction);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", get_cCTActionBoundedCam);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", get_cCTActionSwitchCam);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", get_cCTActionSpline);

//100%
INCLUDE_ASM("camera/trigger/cameratriggerfactory", get_cCTActionNone__FPvPi);
#ifdef SKIP_ASM
void* get_cCTActionNone(void* unused, int* outType)
{
    *outType = 3;
    return 0;
}
#endif

INCLUDE_ASM("camera/trigger/cameratriggerfactory", get_camboundobj);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", get_cCTBoundObjEllipse);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", get_cCTBoundObjBox);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", get_cCTBoundObjLine);

struct sBoundObjVTable {
    char pad_0x00[0x8];
    short field_0x8;
    char pad_0xA[2];
    void* (*fn)(void*); // 0xC
};

struct sBoundObjPoint {
    char pad_0x00[0x24];
    sBoundObjVTable* vtable;
    int field_0x28;
};

extern "C" void* get_t3Vector(void* self, void* v);

//100%
INCLUDE_ASM("camera/trigger/cameratriggerfactory", get_cCTBoundObjPoint__FPvP14sBoundObjPoint);
#ifdef SKIP_ASM
void* get_cCTBoundObjPoint(void* self, sBoundObjPoint* obj)
{
    obj->field_0x28 = 3;
    void* result = obj->vtable->fn((char*)obj + obj->vtable->field_0x8);
    return get_t3Vector(self, result);
}
#endif

INCLUDE_ASM("camera/trigger/cameratriggerfactory", get_camspline);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00171FA8);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_001721C0);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00172278);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00172840);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_001728F8);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", get_camvolume);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", get_cCTVolumeEllipse);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", get_cCTVolumeBox);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_001731C0);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00173208);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_001732B8);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_001732E8);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00173678);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_001736E0);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00173E40);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00174190);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_001741D8);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00174200);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_001744B0);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_001747A0);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00174848);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00175A20);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176328);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176358);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176368);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176398);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_001763C8);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_001763F8);

//100%
INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176440__FPv);
#ifdef SKIP_ASM
void* func_00176440(void* self)
{
    return self;
}
#endif

//100%
INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176448__FPv);
#ifdef SKIP_ASM
void* func_00176448(void* self)
{
    return (char*)self + 0xC;
}
#endif

//100%
INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176450__FPv);
#ifdef SKIP_ASM
void* func_00176450(void* self)
{
    return (char*)self + 0x10;
}
#endif

//100%
INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176458__FPv);
#ifdef SKIP_ASM
void* func_00176458(void* self)
{
    return (char*)self + 0x14;
}
#endif

//100%
INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176460__FPv);
#ifdef SKIP_ASM
void* func_00176460(void* self)
{
    return (char*)self + 0x18;
}
#endif

//100%
INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_001765F8__FPv);
#ifdef SKIP_ASM
void func_001765F8(void* self)
{
}
#endif

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176808);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176840);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176868);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176890);

extern "C" void* func_00175A20(int, int);

//99.38%
INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176A28__FPv);
#ifdef SKIP_ASM
void* func_00176A28(void* self)
{
    return func_00175A20(1, 0xffff);
}
#endif

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176A48);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176A68);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176AA8);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176AD0);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176AE0);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176B10);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176CE0);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176D68);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176DA8);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176DD0);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176DE0);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176E10);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00176FE0);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00177068);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_001770A8);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_001770D0);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_001770E0);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00177110);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_001772E0);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00177368);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_001774C0);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00177520);

//100%
INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00177548__FPv);
#ifdef SKIP_ASM
float func_00177548(void* self)
{
    return 0.0f;
}
#endif

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00177558);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00177588);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00177650);

extern "C" void* func_00177650(int, int);

//99.38%
INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00177E30__FPv);
#ifdef SKIP_ASM
void* func_00177E30(void* self)
{
    return func_00177650(1, 0xffff);
}
#endif

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00177E50);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00177E90);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00177EB8);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00177EC8);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00177EF8);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00177FC0);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00178208);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_001783E0);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00178520);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00178588);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_001785B0);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_001785C0);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_001785F0);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00178758);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_001787E0);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00178938);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_001789E8);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00178B70);

//100%
INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00178B98__FPv);
#ifdef SKIP_ASM
float func_00178B98(void* self)
{
    return 0.0f;
}
#endif

//100%
INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00178BA8__FPvT0);
#ifdef SKIP_ASM
void func_00178BA8(void* self, void* other)
{
    *(int*)((char*)other + 0x10) = 0;
}
#endif

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00178BB0);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00178E90);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00178F58);

extern "C" void* func_00178F58(int, int);

//99.38%
INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00179738__FPv);
#ifdef SKIP_ASM
void* func_00179738(void* self)
{
    return func_00178F58(1, 0xffff);
}
#endif

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00179798);

extern "C" void* func_00179798(int, int);

//99.38%
INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00179FA8__FPv);
#ifdef SKIP_ASM
void* func_00179FA8(void* self)
{
    return func_00179798(1, 0xffff);
}
#endif

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_00179FC8);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_0017A028);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_0017A0B8);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_0017A158);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_0017A220);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_0017A2C8);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_0017A638);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_0017A978);

//100%
INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_0017ABC8__FPv);
#ifdef SKIP_ASM
void* func_0017ABC8(void* self)
{
    int t0 = 0;
    *(int*)((char*)self + 0x4) = t0;
    *(int*)((char*)self + 0x8) = -1;
    *(int*)self = t0;
    return self;
}
#endif

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_0017ABE0);

INCLUDE_ASM("camera/trigger/cameratriggerfactory", func_0017AC98);

