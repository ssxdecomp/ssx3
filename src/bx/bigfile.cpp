#include "common.h"

struct cBigFile {
    int field_0x0;
    int field_0x4;
};

//100%
INCLUDE_ASM("bx/bigfile", cBigFile_cBigFile__FP8cBigFile);
#ifdef SKIP_ASM
cBigFile* cBigFile_cBigFile(cBigFile* self)
{
    self->field_0x4 = 0;
    self->field_0x0 = -1;
    return self;
}
#endif

extern "C" void cBigFile_open(cBigFile* self);

//100%
INCLUDE_ASM("bx/bigfile", cBigFile_cBigFile1__FP8cBigFile);
#ifdef SKIP_ASM
cBigFile* cBigFile_cBigFile1(cBigFile* self)
{
    self->field_0x4 = 0;
    self->field_0x0 = -1;
    cBigFile_open(self);
    return self;
}
#endif

int cBigFile_close(cBigFile* self);
void operator_delete(int* ptr);

//100%
INCLUDE_ASM("bx/bigfile", cBigFile__cBigFile__FP8cBigFilei);
#ifdef SKIP_ASM
void cBigFile__cBigFile(cBigFile* self, int flags)
{
    cBigFile_close(self);
    if (flags & 1) {
        operator_delete((int*)self);
    }
}
#endif

extern "C" void func_003DEDC0(void* handle, int arg);

//90.59% - target keeps a "result=1" store that GCC dead-store-eliminates in ours since it's overwritten before any read; logic is correct
INCLUDE_ASM("bx/bigfile", cBigFile_close__FP8cBigFile);
#ifdef SKIP_ASM
int cBigFile_close(cBigFile* self)
{
    int result = 0;
    if (self->field_0x4 != 0) {
        result = 1;
        func_003DEDC0((void*)(long)self->field_0x0, 0x64);
        result = self->field_0x4 != 0;
    }
    self->field_0x4 = 0;
    return result;
}
#endif

INCLUDE_ASM("bx/bigfile", cBigFile_open);

//100%
INCLUDE_ASM("bx/bigfile", func_00316A00__FPv);
#ifdef SKIP_ASM
void* func_00316A00(void* self)
{
    int t0 = 0;
    *(int*)self = t0;
    *(int*)((char*)self + 0x10) = 0x10;
    *(int*)((char*)self + 0x4) = t0;
    *(int*)((char*)self + 0x8) = t0;
    *(int*)((char*)self + 0xc) = t0;
    return self;
}
#endif

INCLUDE_ASM("bx/bigfile", func_00316A20);

