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

//100%
INCLUDE_ASM("mem/memstd", func_00252658__FPv);
#ifdef SKIP_ASM
int func_00252658(void* self)
{
    return 0;
}
#endif

INCLUDE_ASM("mem/memstd", func_00252660);

INCLUDE_ASM("mem/memstd", func_002526B8);

INCLUDE_ASM("mem/memstd", func_00252980);

extern "C" void* func_00252980(void*);

//90.71%
INCLUDE_ASM("mem/memstd", func_00252F60__FPv);
#ifdef SKIP_ASM
void* func_00252F60(void* self)
{
    return func_00252980(self);
}
#endif

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

extern "C" void* func_002523A8(void* self);

//99.29%
INCLUDE_ASM("mem/memstd", func_00253AF8__FPv);
#ifdef SKIP_ASM
void* func_00253AF8(void* self)
{
    return func_002523A8(self);
}
#endif

INCLUDE_ASM("mem/memstd", func_00253B58);

extern "C" void* func_00253B58(int, int);

//99.38%
INCLUDE_ASM("mem/memstd", func_00254330__FPv);
#ifdef SKIP_ASM
void* func_00254330(void* self)
{
    return func_00253B58(1, 0xffff);
}
#endif

INCLUDE_ASM("mem/memstd", func_00254350);

INCLUDE_ASM("mem/memstd", func_00254368);

INCLUDE_ASM("mem/memstd", func_002543F0);

//96.0%
INCLUDE_ASM("mem/memstd", func_00254400__FPvff);
#ifdef SKIP_ASM
void func_00254400(void* self, float f0, float f1)
{
    *(float*)((char*)self + 0x50) = f1;
    *(float*)((char*)self + 0x4c) = f0;
}
#endif

INCLUDE_ASM("mem/memstd", func_00254410);

INCLUDE_ASM("mem/memstd", func_002547B8);

INCLUDE_ASM("mem/memstd", func_002548D0);

INCLUDE_ASM("mem/memstd", func_00254C48);

extern "C" void* func_002548D0(void* self);

//99.29%
INCLUDE_ASM("mem/memstd", func_00254DA0__FPv);
#ifdef SKIP_ASM
void* func_00254DA0(void* self)
{
    return func_002548D0(self);
}
#endif

INCLUDE_ASM("mem/memstd", func_00254DC0);

INCLUDE_ASM("mem/memstd", func_00254E60);

INCLUDE_ASM("mem/memstd", func_00255638);

//100%
INCLUDE_ASM("mem/memstd", func_00255668__FPv);
#ifdef SKIP_ASM
void func_00255668(void* self)
{
}
#endif

extern "C" void* func_00254E60(int, int);

//99.38%
INCLUDE_ASM("mem/memstd", func_002557C0__FPv);
#ifdef SKIP_ASM
void* func_002557C0(void* self)
{
    return func_00254E60(1, 0xffff);
}
#endif

extern void* D_00481320[];

//100%
INCLUDE_ASM("mem/memstd", func_002557E0__FPv);
#ifdef SKIP_ASM
void* func_002557E0(void* self)
{
    int t0 = 0;
    *(int*)self = t0;
    *(int*)((char*)self + 0x8) = (int)(void*)D_00481320;
    *(int*)((char*)self + 0x4) = t0;
    return self;
}
#endif

INCLUDE_ASM("mem/memstd", func_00255800);

//100%
INCLUDE_ASM("mem/memstd", func_00255830__FPv);
#ifdef SKIP_ASM
int func_00255830(void* self)
{
    int t0 = 1;
    *(int*)((char*)self + 0x4) = 0;
    *(int*)self = t0;
    return t0;
}
#endif

INCLUDE_ASM("mem/memstd", func_00255840);

