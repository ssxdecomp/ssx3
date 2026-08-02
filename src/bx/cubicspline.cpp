#include "common.h"

INCLUDE_ASM("bx/cubicspline", cCubicSplineInterpolant_initCommon);

extern "C" void cCubicSplineInterpolant_initCommon(void* self);

//99.62%
INCLUDE_ASM("bx/cubicspline", func_0031D700__FPv);
#ifdef SKIP_ASM
void func_0031D700(void* self)
{
    cCubicSplineInterpolant_initCommon(self);
    *(int*)self &= -2;
}
#endif

//99.76%
INCLUDE_ASM("bx/cubicspline", func_0031D738__FPvff);
#ifdef SKIP_ASM
void func_0031D738(void* self, float a, float b)
{
    cCubicSplineInterpolant_initCommon(self);
    unsigned int flags = *(unsigned int*)self;
    void* ptr = *(void**)((char*)self + 0x8);
    flags |= 1;
    *(unsigned int*)self = flags;
    *(float*)((char*)ptr + 0x10) = a;
    *(float*)((char*)self + 0x4) = b;
}
#endif

void* cMemMan_free(void* ptr);

//100%
INCLUDE_ASM("bx/cubicspline", func_0031D790__FPv);
#ifdef SKIP_ASM
void func_0031D790(void* self)
{
    if (*(void**)((char*)self + 0x8) != 0) {
        cMemMan_free(*(void**)((char*)self + 0x8));
        *(void**)((char*)self + 0x8) = 0;
    }
    int flags = *(int*)self;
    flags &= -3;
    flags &= -5;
    *(int*)self = flags;
}
#endif

INCLUDE_ASM("bx/cubicspline", func_0031D7E0);

INCLUDE_ASM("bx/cubicspline", func_0031D8B0);

INCLUDE_ASM("bx/cubicspline", func_0031DEE0);

INCLUDE_ASM("bx/cubicspline", func_0031E1D8);

//86.24%
INCLUDE_ASM("bx/cubicspline", func_0031E260__FPv);
#ifdef SKIP_ASM
void func_0031E260(void* self)
{
    char* p = (char*)self + 0x38;
    for (int i = 0x5E; i >= 0; i--) {
        *(void**)(p + 0xC) = p;
        *(void**)(p + 0x8) = p;
        p += 8;
    }
    int flags = *(int*)self;
    int f360 = *(int*)((char*)self + 0x360);
    flags = (flags & 3) | 0x50;
    f360 |= 1;
    *(int*)((char*)self + 0x34C) = 0x40000;
    *(int*)((char*)self + 0x35C) = 0x1000;
    *(int*)((char*)self + 0x344) = 0x8000;
    *(int*)((char*)self + 0x360) = f360;
    *(int*)self = flags;
    *(void**)((char*)self + 0x30) = (char*)self + 0x38;
    *(int*)((char*)self + 0x348) = 0;
    *(int*)((char*)self + 0x354) = 0;
}
#endif

INCLUDE_ASM("bx/cubicspline", func_0031E2D8);

INCLUDE_ASM("bx/cubicspline", func_0031E6D8);

INCLUDE_ASM("bx/cubicspline", func_0031E818);

INCLUDE_ASM("bx/cubicspline", func_0031ED60);

INCLUDE_ASM("bx/cubicspline", func_0031EEE8);

INCLUDE_ASM("bx/cubicspline", func_0031F2C8);

INCLUDE_ASM("bx/cubicspline", func_0031F4E8);

//48%
INCLUDE_ASM("bx/cubicspline", func_0031FBB8__FPvT0);
#ifdef SKIP_ASM
void* func_0031FBB8(void* self, void* ptr)
{
    if (ptr == 0) {
        return 0;
    }
    int flags = *(int*)((char*)ptr - 4);
    if (flags & 2) {
        return (void*)((flags & ~3) - 8);
    }
    char* p8 = (char*)ptr - 8;
    void* p2 = p8 + (flags & ~1);
    int flags2 = *(int*)((char*)p2 + 4);
    if (!(flags2 & 1)) {
        return 0;
    }
    return (void*)((flags & ~3) - 4);
}
#endif

INCLUDE_ASM("bx/cubicspline", func_0031FC20);

//100%
INCLUDE_ASM("bx/cubicspline", func_0031FF20__FPv);
#ifdef SKIP_ASM
void* func_0031FF20(void* self)
{
    *(int*)((char*)self + 0x4) = 0;
    *(int*)((char*)self + 0x8) = 0;
    *(int*)((char*)self + 0xC) = 0;
    *(int*)((char*)self + 0x0) = 0;
    return self;
}
#endif

void operator_delete(int* ptr);

//100%
INCLUDE_ASM("bx/cubicspline", func_0031FF38__FPvi);
#ifdef SKIP_ASM
void func_0031FF38(void* self, int flags)
{
    if (flags & 1) {
        operator_delete((int*)self);
    }
}
#endif

INCLUDE_ASM("bx/cubicspline", func_0031FF60);

INCLUDE_ASM("bx/cubicspline", func_0031FFD8);

extern "C" int func_0031F2C8(void* self);

//99.29%
INCLUDE_ASM("bx/cubicspline", func_00320058__FPv);
#ifdef SKIP_ASM
int func_00320058(void* self)
{
    return func_0031F2C8(self);
}
#endif

extern "C" int func_0031F4E8(void* self);

//99.29%
INCLUDE_ASM("bx/cubicspline", func_00320078__FPv);
#ifdef SKIP_ASM
int func_00320078(void* self)
{
    return func_0031F4E8(self);
}
#endif

extern "C" int func_0031ED60(void* self);

//100%
INCLUDE_ASM("bx/cubicspline", func_003200C0__FPv);
#ifdef SKIP_ASM
int func_003200C0(void* self)
{
    return func_0031ED60(self);
}
#endif

//100%
INCLUDE_ASM("bx/cubicspline", func_003200E8__FPv);
#ifdef SKIP_ASM
void* func_003200E8(void* self)
{
    *(void**)((char*)self + 0x800) = self;
    char* p = (char*)self;
    char* next = (char*)self + 8;
    for (unsigned int i = 0; i < 0xFF; i++) {
        *(void**)p = next;
        p += 8;
        next += 8;
    }
    *(int*)((char*)self + 0x7F8) = 0;
    return self;
}
#endif

//100%
INCLUDE_ASM("bx/cubicspline", func_00320120__FPv);
#ifdef SKIP_ASM
void* func_00320120(void* self)
{
    *(void**)((char*)self + 0x2000) = self;
    char* p = (char*)self;
    char* next = (char*)self + 0x10;
    for (unsigned int i = 0; i < 0x1FF; i++) {
        *(void**)p = next;
        p += 0x10;
        next += 0x10;
    }
    *(int*)((char*)self + 0x1FF0) = 0;
    return self;
}
#endif

//100%
INCLUDE_ASM("bx/cubicspline", func_00320158__FPv);
#ifdef SKIP_ASM
void* func_00320158(void* self)
{
    *(void**)((char*)self + 0x6000) = self;
    char* p = (char*)self;
    char* next = (char*)self + 0x20;
    for (unsigned int i = 0; i < 0x2FF; i++) {
        *(void**)p = next;
        p += 0x20;
        next += 0x20;
    }
    *(int*)((char*)self + 0x5FE0) = 0;
    return self;
}
#endif

//100%
INCLUDE_ASM("bx/cubicspline", func_00320190__FPv);
#ifdef SKIP_ASM
void* func_00320190(void* self)
{
    unsigned int i = 0;
    *(void**)((char*)self + 0x32000) = self;
    char* p = (char*)self;
    char* next = (char*)self + 0x40;
    for (; i < 0xC7F; i++) {
        *(void**)p = next;
        p += 0x40;
        next += 0x40;
    }
    *(int*)((char*)self + 0x31FC0) = 0;
    return self;
}
#endif

//100%
INCLUDE_ASM("bx/cubicspline", func_003201D8__FPv);
#ifdef SKIP_ASM
void* func_003201D8(void* self)
{
    unsigned int i = 0;
    *(void**)((char*)self + 0x25800) = self;
    char* p = (char*)self;
    char* next = (char*)self + 0x80;
    for (; i < 0x4AF; i++) {
        *(void**)p = next;
        p += 0x80;
        next += 0x80;
    }
    *(int*)((char*)self + 0x25780) = 0;
    return self;
}
#endif

//100%
INCLUDE_ASM("bx/cubicspline", func_00320220__FPv);
#ifdef SKIP_ASM
void* func_00320220(void* self)
{
    unsigned int i = 0;
    *(void**)((char*)self + 0x20000) = self;
    char* p = (char*)self;
    char* next = (char*)self + 0x100;
    for (; i < 0x1FF; i++) {
        *(void**)p = next;
        p += 0x100;
        next += 0x100;
    }
    *(int*)((char*)self + 0x1FF00) = 0;
    return self;
}
#endif

//100%
INCLUDE_ASM("bx/cubicspline", func_00320270__FPv);
#ifdef SKIP_ASM
void* func_00320270(void* self)
{
    unsigned int i = 0;
    *(void**)((char*)self + 0x20000) = self;
    char* p = (char*)self;
    char* next = (char*)self + 0x200;
    for (; i < 0xFF; i++) {
        *(void**)p = next;
        p += 0x200;
        next += 0x200;
    }
    *(int*)((char*)self + 0x1FE00) = 0;
    return self;
}
#endif

extern "C" void* func_00319E48(int size);

//100%
INCLUDE_ASM("bx/cubicspline", func_003202C0__FPv);
#ifdef SKIP_ASM
void* func_003202C0(void* self)
{
    void* node = *(void**)((char*)self + 0x800);
    if (node != 0) {
        void* next = *(void**)node;
        *(void**)((char*)self + 0x800) = next;
        return node;
    }
    return func_00319E48(0xC);
}
#endif

//100%
INCLUDE_ASM("bx/cubicspline", func_003202F8__FPv);
#ifdef SKIP_ASM
void* func_003202F8(void* self)
{
    void* node = *(void**)((char*)self + 0x2000);
    if (node != 0) {
        void* next = *(void**)node;
        *(void**)((char*)self + 0x2000) = next;
        return node;
    }
    return func_00319E48(0x14);
}
#endif

//100%
INCLUDE_ASM("bx/cubicspline", func_00320330__FPv);
#ifdef SKIP_ASM
void* func_00320330(void* self)
{
    void* node = *(void**)((char*)self + 0x6000);
    if (node != 0) {
        void* next = *(void**)node;
        *(void**)((char*)self + 0x6000) = next;
        return node;
    }
    return func_00319E48(0x24);
}
#endif

//71.26%
INCLUDE_ASM("bx/cubicspline", func_00320368__FPv);
#ifdef SKIP_ASM
void* func_00320368(void* self)
{
    void* node = *(void**)((char*)self + 0x32000);
    if (node != 0) {
        void* next = *(void**)node;
        *(void**)((char*)self + 0x32000) = next;
        return node;
    }
    return func_00319E48(0x44);
}
#endif

//71.26%
INCLUDE_ASM("bx/cubicspline", func_003203B8__FPv);
#ifdef SKIP_ASM
void* func_003203B8(void* self)
{
    void* node = *(void**)((char*)self + 0x25800);
    if (node != 0) {
        void* next = *(void**)node;
        *(void**)((char*)self + 0x25800) = next;
        return node;
    }
    return func_00319E48(0x84);
}
#endif

//92.5%
INCLUDE_ASM("bx/cubicspline", func_00320408__FPv);
#ifdef SKIP_ASM
void* func_00320408(void* self)
{
    void* node = *(void**)((char*)self + 0x20000);
    if (node != 0) {
        void* next = *(void**)node;
        *(void**)((char*)self + 0x20000) = next;
        return node;
    }
    return func_00319E48(0x104);
}
#endif

//92.5%
INCLUDE_ASM("bx/cubicspline", func_00320448__FPv);
#ifdef SKIP_ASM
void* func_00320448(void* self)
{
    void* node = *(void**)((char*)self + 0x20000);
    if (node != 0) {
        void* next = *(void**)node;
        *(void**)((char*)self + 0x20000) = next;
        return node;
    }
    return func_00319E48(0x204);
}
#endif

//100%
INCLUDE_ASM("bx/cubicspline", func_00320488__FPvPPv);
#ifdef SKIP_ASM
void func_00320488(void* self, void** node)
{
    *node = *(void**)((char*)self + 0x800);
    *(void**)((char*)self + 0x800) = node;
}
#endif

//100%
INCLUDE_ASM("bx/cubicspline", func_00320498__FPvPPv);
#ifdef SKIP_ASM
void func_00320498(void* self, void** node)
{
    *node = *(void**)((char*)self + 0x2000);
    *(void**)((char*)self + 0x2000) = node;
}
#endif

//100%
INCLUDE_ASM("bx/cubicspline", func_003204A8__FPvPPv);
#ifdef SKIP_ASM
void func_003204A8(void* self, void** node)
{
    *node = *(void**)((char*)self + 0x6000);
    *(void**)((char*)self + 0x6000) = node;
}
#endif

//100%
INCLUDE_ASM("bx/cubicspline", func_003204B8__FPvPPv);
#ifdef SKIP_ASM
void func_003204B8(void* self, void** node)
{
    *node = *(void**)((char*)self + 0x32000);
    *(void**)((char*)self + 0x32000) = node;
}
#endif

//100%
INCLUDE_ASM("bx/cubicspline", func_003204D0__FPvPPv);
#ifdef SKIP_ASM
void func_003204D0(void* self, void** node)
{
    *node = *(void**)((char*)self + 0x25800);
    *(void**)((char*)self + 0x25800) = node;
}
#endif

//100%
INCLUDE_ASM("bx/cubicspline", func_003204E8__FPvPPv);
#ifdef SKIP_ASM
void func_003204E8(void* self, void** node)
{
    *node = *(void**)((char*)self + 0x20000);
    *(void**)((char*)self + 0x20000) = node;
}
#endif

//100%
INCLUDE_ASM("bx/cubicspline", func_00320500__FPvPPv);
#ifdef SKIP_ASM
void func_00320500(void* self, void** node)
{
    *node = *(void**)((char*)self + 0x20000);
    *(void**)((char*)self + 0x20000) = node;
}
#endif

//100%
INCLUDE_ASM("bx/cubicspline", func_00320518__Fv);
#ifdef SKIP_ASM
void func_00320518(void)
{
}
#endif

//100%
INCLUDE_ASM("bx/cubicspline", func_00320520__Fv);
#ifdef SKIP_ASM
void func_00320520(void)
{
}
#endif

//100%
INCLUDE_ASM("bx/cubicspline", func_00320528__Fv);
#ifdef SKIP_ASM
void func_00320528(void)
{
}
#endif

//100%
INCLUDE_ASM("bx/cubicspline", func_00320530__Fv);
#ifdef SKIP_ASM
void func_00320530(void)
{
}
#endif

//100%
INCLUDE_ASM("bx/cubicspline", func_00320538__Fv);
#ifdef SKIP_ASM
void func_00320538(void)
{
}
#endif

//100%
INCLUDE_ASM("bx/cubicspline", func_00320540__Fv);
#ifdef SKIP_ASM
void func_00320540(void)
{
}
#endif

//100%
INCLUDE_ASM("bx/cubicspline", func_00320548__Fv);
#ifdef SKIP_ASM
void func_00320548(void)
{
}
#endif

INCLUDE_ASM("bx/cubicspline", func_00320550);
