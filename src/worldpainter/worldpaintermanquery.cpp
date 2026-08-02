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

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1458);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1460);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1490);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1498);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14A0);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14A8);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14B0);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14B8);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14C0);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14C8);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14D0);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14D8);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14E0);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14E8);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14F0);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C14F8);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1500);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1508);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1510);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1518);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1520);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1528);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1530);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1538);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1540);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1548);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1550);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1558);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1560);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1568);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1570);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1578);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1580);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1588);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1590);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1598);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15A0);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15A8);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15B0);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15B8);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15C0);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15C8);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15D0);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15D8);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15E0);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15E8);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15F0);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C15F8);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1600);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1608);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1610);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1618);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1620);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1628);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1630);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1638);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1640);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1648);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1650);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1658);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1660);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1668);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1670);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1678);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1680);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C1688);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C16B8);

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C17C0);

