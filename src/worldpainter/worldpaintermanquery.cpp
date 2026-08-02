#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* cWorldPainterQuery_cWorldPainterQuery(void* self, void* arg);
extern const char D_00483DE8[];

struct cWorldPainterManArg {
    void* field_0x0;
};

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", cWorldPainterMan_getQuery__FPvP19cWorldPainterManArg);
#ifdef SKIP_ASM
void* cWorldPainterMan_getQuery(void* self, cWorldPainterManArg* x)
{
    void* mem = cMemMan_alloc(0x18, D_00483DE8, 0, 0);
    void* arg = x->field_0x0;
    return cWorldPainterQuery_cWorldPainterQuery(mem, arg);
}
#endif

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C0B70);

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1458__FPv);
#ifdef SKIP_ASM
void func_002C1458(void* self)
{
}
#endif

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1460);

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1490__FPv);
#ifdef SKIP_ASM
void* func_002C1490(void* self)
{
    return (char*)self + 0x8;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1498__FPv);
#ifdef SKIP_ASM
void* func_002C1498(void* self)
{
    return (char*)self + 0x10;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14A0__FPv);
#ifdef SKIP_ASM
void* func_002C14A0(void* self)
{
    return (char*)self + 0x8;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14A8__FPv);
#ifdef SKIP_ASM
void* func_002C14A8(void* self)
{
    return (char*)self + 0x8;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14B0__FPv);
#ifdef SKIP_ASM
void* func_002C14B0(void* self)
{
    return (char*)self + 0x8;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14B8__FPv);
#ifdef SKIP_ASM
void* func_002C14B8(void* self)
{
    return (char*)self + 0x8;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14C0__FPv);
#ifdef SKIP_ASM
void* func_002C14C0(void* self)
{
    return (char*)self + 0x8;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14C8__FPv);
#ifdef SKIP_ASM
void* func_002C14C8(void* self)
{
    return (char*)self + 0x10;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14D0__FPv);
#ifdef SKIP_ASM
void* func_002C14D0(void* self)
{
    return (char*)self + 0x18;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14D8__FPv);
#ifdef SKIP_ASM
void* func_002C14D8(void* self)
{
    return (char*)self + 0x20;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14E0__FPv);
#ifdef SKIP_ASM
void* func_002C14E0(void* self)
{
    return (char*)self + 0x28;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14E8__FPv);
#ifdef SKIP_ASM
void* func_002C14E8(void* self)
{
    return (char*)self + 0x30;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14F0__FPv);
#ifdef SKIP_ASM
void* func_002C14F0(void* self)
{
    return (char*)self + 0x8;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14F8__FPv);
#ifdef SKIP_ASM
void* func_002C14F8(void* self)
{
    return (char*)self + 0x10;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1500__FPv);
#ifdef SKIP_ASM
void* func_002C1500(void* self)
{
    return (char*)self + 0x18;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1508__FPv);
#ifdef SKIP_ASM
void* func_002C1508(void* self)
{
    return (char*)self + 0x20;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1510__FPv);
#ifdef SKIP_ASM
void* func_002C1510(void* self)
{
    return (char*)self + 0x28;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1518__FPv);
#ifdef SKIP_ASM
void* func_002C1518(void* self)
{
    return (char*)self + 0x30;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1520__FPv);
#ifdef SKIP_ASM
void* func_002C1520(void* self)
{
    return (char*)self + 0x38;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1528__FPv);
#ifdef SKIP_ASM
void* func_002C1528(void* self)
{
    return (char*)self + 0x8;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1530__FPv);
#ifdef SKIP_ASM
void* func_002C1530(void* self)
{
    return (char*)self + 0x10;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1538__FPv);
#ifdef SKIP_ASM
void* func_002C1538(void* self)
{
    return (char*)self + 0x18;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1540__FPv);
#ifdef SKIP_ASM
void* func_002C1540(void* self)
{
    return (char*)self + 0x20;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1548__FPv);
#ifdef SKIP_ASM
void* func_002C1548(void* self)
{
    return (char*)self + 0x28;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1550__FPv);
#ifdef SKIP_ASM
void* func_002C1550(void* self)
{
    return (char*)self + 0x30;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1558__FPv);
#ifdef SKIP_ASM
void* func_002C1558(void* self)
{
    return (char*)self + 0x8;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1560__FPv);
#ifdef SKIP_ASM
void* func_002C1560(void* self)
{
    return (char*)self + 0x8;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1568__FPv);
#ifdef SKIP_ASM
void* func_002C1568(void* self)
{
    return (char*)self + 0x10;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1570__FPv);
#ifdef SKIP_ASM
void* func_002C1570(void* self)
{
    return (char*)self + 0x18;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1578__FPv);
#ifdef SKIP_ASM
void* func_002C1578(void* self)
{
    return (char*)self + 0x20;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1580__FPv);
#ifdef SKIP_ASM
void* func_002C1580(void* self)
{
    return (char*)self + 0x28;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1588__FPv);
#ifdef SKIP_ASM
void* func_002C1588(void* self)
{
    return (char*)self + 0x30;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1590__FPv);
#ifdef SKIP_ASM
void* func_002C1590(void* self)
{
    return (char*)self + 0x38;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1598__FPv);
#ifdef SKIP_ASM
void* func_002C1598(void* self)
{
    return (char*)self + 0x40;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15A0__FPv);
#ifdef SKIP_ASM
void* func_002C15A0(void* self)
{
    return (char*)self + 0x48;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15A8__FPv);
#ifdef SKIP_ASM
void* func_002C15A8(void* self)
{
    return (char*)self + 0x8;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15B0__FPv);
#ifdef SKIP_ASM
void* func_002C15B0(void* self)
{
    return (char*)self + 0x8;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15B8__FPv);
#ifdef SKIP_ASM
void* func_002C15B8(void* self)
{
    return (char*)self + 0x18;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15C0__FPv);
#ifdef SKIP_ASM
void* func_002C15C0(void* self)
{
    return (char*)self + 0x28;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15C8__FPv);
#ifdef SKIP_ASM
void* func_002C15C8(void* self)
{
    return (char*)self + 0x38;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15D0__FPv);
#ifdef SKIP_ASM
void* func_002C15D0(void* self)
{
    return (char*)self + 0x48;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15D8__FPv);
#ifdef SKIP_ASM
void* func_002C15D8(void* self)
{
    return (char*)self + 0x50;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15E0__FPv);
#ifdef SKIP_ASM
void* func_002C15E0(void* self)
{
    return (char*)self + 0x8;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15E8__FPv);
#ifdef SKIP_ASM
void* func_002C15E8(void* self)
{
    return (char*)self + 0x10;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15F0__FPv);
#ifdef SKIP_ASM
void* func_002C15F0(void* self)
{
    return (char*)self + 0x18;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15F8__FPv);
#ifdef SKIP_ASM
void* func_002C15F8(void* self)
{
    return (char*)self + 0x20;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1600__FPv);
#ifdef SKIP_ASM
void* func_002C1600(void* self)
{
    return (char*)self + 0x28;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1608__FPv);
#ifdef SKIP_ASM
void* func_002C1608(void* self)
{
    return (char*)self + 0x30;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1610__FPv);
#ifdef SKIP_ASM
void* func_002C1610(void* self)
{
    return (char*)self + 0x38;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1618__FPv);
#ifdef SKIP_ASM
void* func_002C1618(void* self)
{
    return (char*)self + 0x40;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1620__FPv);
#ifdef SKIP_ASM
void* func_002C1620(void* self)
{
    return (char*)self + 0x48;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1628__FPv);
#ifdef SKIP_ASM
void* func_002C1628(void* self)
{
    return (char*)self + 0x50;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1630__FPv);
#ifdef SKIP_ASM
void* func_002C1630(void* self)
{
    return (char*)self + 0x58;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1638__FPv);
#ifdef SKIP_ASM
void* func_002C1638(void* self)
{
    return (char*)self + 0x60;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1640__FPv);
#ifdef SKIP_ASM
void* func_002C1640(void* self)
{
    return (char*)self + 0x68;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1648__FPv);
#ifdef SKIP_ASM
void* func_002C1648(void* self)
{
    return (char*)self + 0x70;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1650__FPv);
#ifdef SKIP_ASM
void* func_002C1650(void* self)
{
    return (char*)self + 0x78;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1658__FPv);
#ifdef SKIP_ASM
void* func_002C1658(void* self)
{
    return (char*)self + 0x80;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1660__FPv);
#ifdef SKIP_ASM
void* func_002C1660(void* self)
{
    return (char*)self + 0x88;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1668__FPv);
#ifdef SKIP_ASM
void* func_002C1668(void* self)
{
    return (char*)self + 0x90;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1670__FPv);
#ifdef SKIP_ASM
void* func_002C1670(void* self)
{
    return (char*)self + 0x98;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1678__FPv);
#ifdef SKIP_ASM
void* func_002C1678(void* self)
{
    return (char*)self + 0x8;
}
#endif

//100%
INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1680__FPv);
#ifdef SKIP_ASM
void* func_002C1680(void* self)
{
    return (char*)self + 0x10;
}
#endif

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1688);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C16B8);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C17C0);

