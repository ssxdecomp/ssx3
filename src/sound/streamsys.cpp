#include "common.h"

INCLUDE_ASM("sound/streamsys", cStreamInstance_cStreamInstance);

INCLUDE_ASM("sound/streamsys", func_002A9DF0);

INCLUDE_ASM("sound/streamsys", func_002A9E78);

INCLUDE_ASM("sound/streamsys", func_002A9ED8);

//100%
INCLUDE_ASM("sound/streamsys", func_002A9F30__FPvi);
#ifdef SKIP_ASM
void func_002A9F30(void* self, int val)
{
    *(char*)((char*)self + 0xC) = (char)val;
}
#endif

INCLUDE_ASM("sound/streamsys", func_002A9F38);

INCLUDE_ASM("sound/streamsys", func_002A9F80);

INCLUDE_ASM("sound/streamsys", func_002AA020);

INCLUDE_ASM("sound/streamsys", func_002AA068);

INCLUDE_ASM("sound/streamsys", func_002AA108);

INCLUDE_ASM("sound/streamsys", func_002AA1B8);

INCLUDE_ASM("sound/streamsys", func_002AA210);

INCLUDE_ASM("sound/streamsys", func_002AA320);

extern "C" void* func_003B78F8(int);

//100%
INCLUDE_ASM("sound/streamsys", func_002AA408__FPv);
#ifdef SKIP_ASM
void* func_002AA408(void* self)
{
    return func_003B78F8(*(int*)((char*)self + 0x8));
}
#endif

INCLUDE_ASM("sound/streamsys", func_002AA428);

INCLUDE_ASM("sound/streamsys", cStreamSys_cStreamSys);

INCLUDE_ASM("sound/streamsys", func_002AA648);

INCLUDE_ASM("sound/streamsys", func_002AA7F0);

INCLUDE_ASM("sound/streamsys", func_002AA910);

INCLUDE_ASM("sound/streamsys", func_002AAB98);

INCLUDE_ASM("sound/streamsys", func_002AABD0);

INCLUDE_ASM("sound/streamsys", func_002AAC28);

INCLUDE_ASM("sound/streamsys", func_002AAD78);

INCLUDE_ASM("sound/streamsys", func_002AAE08);

INCLUDE_ASM("sound/streamsys", func_002AAE40);

INCLUDE_ASM("sound/streamsys", func_002AAE78);

INCLUDE_ASM("sound/streamsys", func_002AB028);

INCLUDE_ASM("sound/streamsys", func_002AB0D0);

INCLUDE_ASM("sound/streamsys", func_002AB150);

//100%
INCLUDE_ASM("sound/streamsys", func_002AB188__FPvi);
#ifdef SKIP_ASM
int func_002AB188(void* self, int a1)
{
    return *(int*)((char*)*(void**)((char*)self + 0x8) + a1 * 4);
}
#endif

INCLUDE_ASM("sound/streamsys", func_002AB200);

INCLUDE_ASM("sound/streamsys", func_002AB478);

INCLUDE_ASM("sound/streamsys", func_002AB6B0);

INCLUDE_ASM("sound/streamsys", func_002AB7A0);

INCLUDE_ASM("sound/streamsys", func_002AB828);

INCLUDE_ASM("sound/streamsys", func_002AB8E8);

INCLUDE_ASM("sound/streamsys", func_002AB958);

INCLUDE_ASM("sound/streamsys", func_002AB9E0);

INCLUDE_ASM("sound/streamsys", func_002ABA18);

INCLUDE_ASM("sound/streamsys", func_002ABA40);

INCLUDE_ASM("sound/streamsys", func_002ABB38);

INCLUDE_ASM("sound/streamsys", func_002ABB80);

INCLUDE_ASM("sound/streamsys", func_002ABC18);

extern "C" void* func_002ABC18(int);

//99.29%
INCLUDE_ASM("sound/streamsys", func_002ABC80__FPvi);
#ifdef SKIP_ASM
void* func_002ABC80(void* self, int a1)
{
    return func_002ABC18(a1);
}
#endif

INCLUDE_ASM("sound/streamsys", func_002ABCA0);

//96.0%
INCLUDE_ASM("sound/streamsys", func_002ABCE8__FPvii);
#ifdef SKIP_ASM
void func_002ABCE8(void* self, int a1, int a2)
{
    *(int*)((char*)self + 0x10) = a2;
    *(int*)((char*)self + 0xc) = a1;
}
#endif

INCLUDE_ASM("sound/streamsys", func_002ABCF8);

//96.0%
INCLUDE_ASM("sound/streamsys", func_002ABD38__FPvii);
#ifdef SKIP_ASM
void func_002ABD38(void* self, int a1, int a2)
{
    *(int*)((char*)self + 0x10) = a2;
    *(int*)((char*)self + 0xc) = a1;
}
#endif

INCLUDE_ASM("sound/streamsys", func_002ABD48);

INCLUDE_ASM("sound/streamsys", func_002ABD90);

INCLUDE_ASM("sound/streamsys", func_002ABE78);

INCLUDE_ASM("sound/streamsys", func_002ABF60);

INCLUDE_ASM("sound/streamsys", func_002AC180);

INCLUDE_ASM("sound/streamsys", func_002AC220);

INCLUDE_ASM("sound/streamsys", func_002AC7F0);

INCLUDE_ASM("sound/streamsys", func_002AC868);

INCLUDE_ASM("sound/streamsys", func_002ACAC8);

INCLUDE_ASM("sound/streamsys", func_002ACB30);

INCLUDE_ASM("sound/streamsys", func_002ACB80);

