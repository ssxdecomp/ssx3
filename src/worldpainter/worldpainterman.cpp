#include "common.h"

void cWorldPainterQuery_reset(void* self);

//100%
INCLUDE_ASM("worldpainter/worldpainterman", cWorldPainterMan_reset__FPv);
#ifdef SKIP_ASM
void cWorldPainterMan_reset(void* self)
{
    cWorldPainterQuery_reset(self);
}
#endif

