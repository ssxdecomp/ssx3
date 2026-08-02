#include "common.h"

INCLUDE_ASM("mem/memstd", MEMCLASS_create);

INCLUDE_ASM("mem/memstd", MEMCLASS_link);

INCLUDE_ASM("mem/memstd", func_00251F68);

extern const char D_004800A8[];
void func_00251F68();
void MEM_printclassf(void* thing, const char* fmt, void (*cb)());

//100%
INCLUDE_ASM("mem/memstd", MEM_printclass__FPv);
#ifdef SKIP_ASM
void MEM_printclass(void* thing)
{
    MEM_printclassf(thing, D_004800A8, func_00251F68);
}
#endif

extern void* D_004A2E78;

//99.25%
INCLUDE_ASM("mem/memstd", MEM_print__Fv);
#ifdef SKIP_ASM
void MEM_print()
{
    MEM_printclass(D_004A2E78);
}
#endif

INCLUDE_ASM("mem/memstd", MEM_printclassf);

INCLUDE_ASM("mem/memstd", func_00252248);

INCLUDE_ASM("mem/memstd", func_002522B0);

INCLUDE_ASM("mem/memstd", func_002523A8);

INCLUDE_ASM("mem/memstd", func_00252658);

INCLUDE_ASM("mem/memstd", func_00252660);

INCLUDE_ASM("mem/memstd", func_002526B8);

INCLUDE_ASM("mem/memstd", func_00252980);

INCLUDE_ASM("mem/memstd", func_00252F60);

INCLUDE_ASM("mem/memstd", func_00252FA0);

INCLUDE_ASM("mem/memstd", func_00253390);

INCLUDE_ASM("mem/memstd", func_002533C8);

INCLUDE_ASM("mem/memstd", func_00253418);

INCLUDE_ASM("mem/memstd", func_002534A8);

INCLUDE_ASM("mem/memstd", func_002535F8);

INCLUDE_ASM("mem/memstd", func_002536C8);

INCLUDE_ASM("mem/memstd", func_00253860);

INCLUDE_ASM("mem/memstd", func_00253890);

INCLUDE_ASM("mem/memstd", func_00253938);

INCLUDE_ASM("mem/memstd", func_002539E0);

INCLUDE_ASM("mem/memstd", func_00253A40);

INCLUDE_ASM("mem/memstd", func_00253AA0);

INCLUDE_ASM("mem/memstd", func_00253AD0);

INCLUDE_ASM("mem/memstd", func_00253AF8);

INCLUDE_ASM("mem/memstd", func_00253B58);

INCLUDE_ASM("mem/memstd", func_00254330);

INCLUDE_ASM("mem/memstd", func_00254350);

INCLUDE_ASM("mem/memstd", func_00254368);

INCLUDE_ASM("mem/memstd", func_002543F0);

INCLUDE_ASM("mem/memstd", func_00254400);

INCLUDE_ASM("mem/memstd", func_00254410);

INCLUDE_ASM("mem/memstd", func_002547B8);

INCLUDE_ASM("mem/memstd", func_002548D0);

INCLUDE_ASM("mem/memstd", func_00254C48);

INCLUDE_ASM("mem/memstd", func_00254DA0);

INCLUDE_ASM("mem/memstd", func_00254DC0);

INCLUDE_ASM("mem/memstd", func_00254E60);

INCLUDE_ASM("mem/memstd", func_00255638);

INCLUDE_ASM("mem/memstd", func_00255668);

INCLUDE_ASM("mem/memstd", func_002557C0);

INCLUDE_ASM("mem/memstd", func_002557E0);

INCLUDE_ASM("mem/memstd", func_00255800);

INCLUDE_ASM("mem/memstd", func_00255830);

INCLUDE_ASM("mem/memstd", func_00255840);

