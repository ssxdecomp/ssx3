#include "common.h"

INCLUDE_ASM("worldpainter/quadtree", cQuadTree_getFreeNode);

INCLUDE_ASM("worldpainter/quadtree", func_002C1CD8);

INCLUDE_ASM("worldpainter/quadtree", cQuadTree_exportTree);

INCLUDE_ASM("worldpainter/quadtree", func_002C2088);

INCLUDE_ASM("worldpainter/quadtree", func_002C2210);

INCLUDE_ASM("worldpainter/quadtree", func_002C2268);

INCLUDE_ASM("worldpainter/quadtree", func_002C22C8);

INCLUDE_ASM("worldpainter/quadtree", func_002C2300);

INCLUDE_ASM("worldpainter/quadtree", func_002C2338);

INCLUDE_ASM("worldpainter/quadtree", func_002C2430);

INCLUDE_ASM("worldpainter/quadtree", func_002C24D0);

INCLUDE_ASM("worldpainter/quadtree", func_002C2508);

INCLUDE_ASM("worldpainter/quadtree", func_002C2540);

INCLUDE_ASM("worldpainter/quadtree", func_002C2580);

INCLUDE_ASM("worldpainter/quadtree", func_002C25B8);

INCLUDE_ASM("worldpainter/quadtree", func_002C2688);

INCLUDE_ASM("worldpainter/quadtree", func_002C26D0);

INCLUDE_ASM("worldpainter/quadtree", func_002C2718);

INCLUDE_ASM("worldpainter/quadtree", func_002C27C0);

INCLUDE_ASM("worldpainter/quadtree", func_002C2868);

INCLUDE_ASM("worldpainter/quadtree", func_002C2F18);

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C3FA0__FPv);
#ifdef SKIP_ASM
void func_002C3FA0(void* self)
{
}
#endif

INCLUDE_ASM("worldpainter/quadtree", func_002C3FA8);

INCLUDE_ASM("worldpainter/quadtree", func_002C3FE0);

INCLUDE_ASM("worldpainter/quadtree", func_002C4050);

INCLUDE_ASM("worldpainter/quadtree", func_002C4198);

INCLUDE_ASM("worldpainter/quadtree", func_002C41D8);

INCLUDE_ASM("worldpainter/quadtree", func_002C4210);

extern "C" void* func_002C48C0(void*, int);

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C4290__FPvi);
#ifdef SKIP_ASM
void* func_002C4290(void* self, int a1)
{
    *(int*)((char*)self + 0x1c) = a1;
    return func_002C48C0(self, 0x22);
}
#endif

INCLUDE_ASM("worldpainter/quadtree", func_002C42B0);

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C4368__FPv);
#ifdef SKIP_ASM
void* func_002C4368(void* self)
{
    return func_002C48C0(self, 0x11);
}
#endif

INCLUDE_ASM("worldpainter/quadtree", func_002C4388);

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C43E0__FPvi);
#ifdef SKIP_ASM
void* func_002C43E0(void* self, int a1)
{
    *(int*)((char*)self + 0x1c) = a1;
    return func_002C48C0(self, 0x13);
}
#endif

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C4400__FPv);
#ifdef SKIP_ASM
int func_002C4400(void* self)
{
    return *(int*)((char*)self + 0x490);
}
#endif

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C4408__FPvi);
#ifdef SKIP_ASM
void func_002C4408(void* self, int val)
{
    *(int*)((char*)self + 0x24) = val;
}
#endif

INCLUDE_ASM("worldpainter/quadtree", func_002C4410);

INCLUDE_ASM("worldpainter/quadtree", func_002C4480);

INCLUDE_ASM("worldpainter/quadtree", func_002C44E0);

INCLUDE_ASM("worldpainter/quadtree", func_002C4520);

INCLUDE_ASM("worldpainter/quadtree", func_002C4578);

INCLUDE_ASM("worldpainter/quadtree", func_002C45D0);

INCLUDE_ASM("worldpainter/quadtree", func_002C4648);

INCLUDE_ASM("worldpainter/quadtree", func_002C46C0);

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C4720__FPvii);
#ifdef SKIP_ASM
void* func_002C4720(void* self, int a1, int a2)
{
    *(int*)((char*)self + 0x2c) = a1;
    *(int*)((char*)self + 0x20) = a2;
    return func_002C48C0(self, 0x17);
}
#endif

INCLUDE_ASM("worldpainter/quadtree", func_002C4748);

//63.33%
INCLUDE_ASM("worldpainter/quadtree", func_002C4758__FPv);
#ifdef SKIP_ASM
int func_002C4758(void* self)
{
    int t0 = 1;
    *(int*)((char*)self + 0x48) = t0;
    return t0;
}
#endif

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C4768__FPv);
#ifdef SKIP_ASM
void* func_002C4768(void* self)
{
    return func_002C48C0(self, 0x18);
}
#endif

INCLUDE_ASM("worldpainter/quadtree", func_002C4788);

INCLUDE_ASM("worldpainter/quadtree", func_002C4800);

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C4858__FPvii);
#ifdef SKIP_ASM
void* func_002C4858(void* self, int a1, int a2)
{
    *(int*)((char*)self + 0x2c) = a1;
    *(int*)((char*)self + 0x20) = a2;
    return func_002C48C0(self, 0x1d);
}
#endif

INCLUDE_ASM("worldpainter/quadtree", func_002C4880);

//63.33%
INCLUDE_ASM("worldpainter/quadtree", func_002C4890__FPv);
#ifdef SKIP_ASM
int func_002C4890(void* self)
{
    int t0 = 1;
    *(int*)((char*)self + 0x44) = t0;
    return t0;
}
#endif

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C48A0__FPv);
#ifdef SKIP_ASM
void* func_002C48A0(void* self)
{
    return func_002C48C0(self, 0x1e);
}
#endif

INCLUDE_ASM("worldpainter/quadtree", func_002C48C0);

INCLUDE_ASM("worldpainter/quadtree", func_002C50E0);

INCLUDE_ASM("worldpainter/quadtree", func_002C5140);

INCLUDE_ASM("worldpainter/quadtree", func_002C5168);

INCLUDE_ASM("worldpainter/quadtree", func_002C51D0);

extern "C" void* func_002C51D0(void*, int);

//99.38%
INCLUDE_ASM("worldpainter/quadtree", func_002C5230__FPv);
#ifdef SKIP_ASM
int func_002C5230(void* self)
{
    return (func_002C51D0(self, *(int*)((char*)self + 0xc)) != 0);
}
#endif

INCLUDE_ASM("worldpainter/quadtree", func_002C5250);

INCLUDE_ASM("worldpainter/quadtree", func_002C5278);

INCLUDE_ASM("worldpainter/quadtree", func_002C52D8);

INCLUDE_ASM("worldpainter/quadtree", func_002C5300);

INCLUDE_ASM("worldpainter/quadtree", func_002C5320);

extern "C" void* func_002C5320(void*, int);

//99.29%
INCLUDE_ASM("worldpainter/quadtree", func_002C5338__FPv);
#ifdef SKIP_ASM
void* func_002C5338(void* self)
{
    return func_002C5320(self, *(int*)((char*)self + 0xc));
}
#endif

INCLUDE_ASM("worldpainter/quadtree", func_002C5358);

INCLUDE_ASM("worldpainter/quadtree", func_002C53B0);

INCLUDE_ASM("worldpainter/quadtree", func_002C53C8);

INCLUDE_ASM("worldpainter/quadtree", func_002C53E0);

INCLUDE_ASM("worldpainter/quadtree", func_002C54D0);

extern "C" void* func_002C2580(void*);

//99.29%
INCLUDE_ASM("worldpainter/quadtree", func_002C5500__FPv);
#ifdef SKIP_ASM
void* func_002C5500(void* self)
{
    return func_002C2580((char*)self + 0x58);
}
#endif

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C5520__FPv);
#ifdef SKIP_ASM
void func_002C5520(void* self)
{
}
#endif

INCLUDE_ASM("worldpainter/quadtree", func_002C5528);

INCLUDE_ASM("worldpainter/quadtree", func_002C5558);

INCLUDE_ASM("worldpainter/quadtree", func_002C5570);

INCLUDE_ASM("worldpainter/quadtree", func_002C5588);

INCLUDE_ASM("worldpainter/quadtree", func_002C55C0);

INCLUDE_ASM("worldpainter/quadtree", func_002C55D8);

INCLUDE_ASM("worldpainter/quadtree", func_002C6128);

INCLUDE_ASM("worldpainter/quadtree", func_002C6280);

INCLUDE_ASM("worldpainter/quadtree", func_002C6360);

INCLUDE_ASM("worldpainter/quadtree", func_002C63E8);

INCLUDE_ASM("worldpainter/quadtree", func_002C63F8);

INCLUDE_ASM("worldpainter/quadtree", func_002C64A8);

INCLUDE_ASM("worldpainter/quadtree", func_002C64D0);

INCLUDE_ASM("worldpainter/quadtree", func_002C64F8);

INCLUDE_ASM("worldpainter/quadtree", func_002C66B8);

INCLUDE_ASM("worldpainter/quadtree", func_002C66D8);

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C6700__FPv);
#ifdef SKIP_ASM
int func_002C6700(void* self)
{
    return 0x1;
}
#endif

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C6708__FPv);
#ifdef SKIP_ASM
int func_002C6708(void* self)
{
    return 0x1;
}
#endif

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C6710__FPv);
#ifdef SKIP_ASM
int func_002C6710(void* self)
{
    return 0x1;
}
#endif

INCLUDE_ASM("worldpainter/quadtree", func_002C6718);

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C6748__FPv);
#ifdef SKIP_ASM
int func_002C6748(void* self)
{
    return 0x4000;
}
#endif

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C6750__FPv);
#ifdef SKIP_ASM
int func_002C6750(void* self)
{
    return -0x1;
}
#endif

INCLUDE_ASM("worldpainter/quadtree", func_002C6758);

INCLUDE_ASM("worldpainter/quadtree", func_002C6778);

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C67A8__FPv);
#ifdef SKIP_ASM
int func_002C67A8(void* self)
{
    return 0;
}
#endif

INCLUDE_ASM("worldpainter/quadtree", func_002C67B0);

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C67E0__FPv);
#ifdef SKIP_ASM
int func_002C67E0(void* self)
{
    return -0x1;
}
#endif

//99.8%
INCLUDE_ASM("worldpainter/quadtree", func_002C67E8__FPvi);
#ifdef SKIP_ASM
void* func_002C67E8(void* self, int a1)
{
    *(int*)((char*)self + 0x10) = a1;
    *(int*)((char*)self + 0xc) = a1;
    return func_002C48C0(self, 3);
}
#endif

INCLUDE_ASM("worldpainter/quadtree", func_002C6810);

INCLUDE_ASM("worldpainter/quadtree", func_002C6848);

INCLUDE_ASM("worldpainter/quadtree", func_002C68C8);

INCLUDE_ASM("worldpainter/quadtree", func_002C68F0);

INCLUDE_ASM("worldpainter/quadtree", func_002C6968);

INCLUDE_ASM("worldpainter/quadtree", func_002C69A0);

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C6A08__FPv);
#ifdef SKIP_ASM
void* func_002C6A08(void* self)
{
    return func_002C48C0(self, 0x49);
}
#endif

INCLUDE_ASM("worldpainter/quadtree", func_002C6A28);

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C6A60__FPvii);
#ifdef SKIP_ASM
void* func_002C6A60(void* self, int a1, int a2)
{
    *(int*)((char*)self + 0x14e4) = a1;
    *(int*)((char*)self + 0x14e8) = a2;
    return func_002C48C0(self, 0x41);
}
#endif

INCLUDE_ASM("worldpainter/quadtree", func_002C6A88);

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C6AE0__FPv);
#ifdef SKIP_ASM
void* func_002C6AE0(void* self)
{
    return func_002C48C0(self, 0x47);
}
#endif

INCLUDE_ASM("worldpainter/quadtree", func_002C6B00);

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C6B50__FPvii);
#ifdef SKIP_ASM
void* func_002C6B50(void* self, int a1, int a2)
{
    *(int*)((char*)self + 0x2c) = a1;
    *(int*)((char*)self + 0x24) = a2;
    return func_002C48C0(self, 0x43);
}
#endif

INCLUDE_ASM("worldpainter/quadtree", func_002C6B78);

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C6BD0__FPvii);
#ifdef SKIP_ASM
void* func_002C6BD0(void* self, int a1, int a2)
{
    *(int*)((char*)self + 0x2c) = a1;
    *(int*)((char*)self + 0x24) = a2;
    return func_002C48C0(self, 0x45);
}
#endif

INCLUDE_ASM("worldpainter/quadtree", func_002C6BF8);

INCLUDE_ASM("worldpainter/quadtree", func_002C6C50);

INCLUDE_ASM("worldpainter/quadtree", func_002C6C88);

INCLUDE_ASM("worldpainter/quadtree", func_002C6CE0);

INCLUDE_ASM("worldpainter/quadtree", func_002C6D18);

INCLUDE_ASM("worldpainter/quadtree", func_002C6D70);

extern "C" void* func_003DBB68(int);

//100%
INCLUDE_ASM("worldpainter/quadtree", func_002C6DC0__FPv);
#ifdef SKIP_ASM
void* func_002C6DC0(void* self)
{
    return func_003DBB68(*(int*)((char*)self + 0x4));
}
#endif

INCLUDE_ASM("worldpainter/quadtree", func_002C6DE0);

INCLUDE_ASM("worldpainter/quadtree", func_002C6E98);

