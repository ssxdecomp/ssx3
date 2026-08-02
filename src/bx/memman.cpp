#include "common.h"

extern unsigned int D_004A3E84;
extern const char D_004A3E88[];
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);

//99.9% - target's gp-rel load has a raw literal offset (no symbol); ours emits a %gp_rel() reloc for the same address, splat won't symbolize target's read to match
INCLUDE_ASM("bx/memman", operator_new1__Fi);
#ifdef SKIP_ASM
void* operator_new1(int size)
{
    return cMemMan_alloc(size, D_004A3E88, D_004A3E84, 0);
}
#endif

//99.9%
INCLUDE_ASM("bx/memman", operator_new2__Fi);
#ifdef SKIP_ASM
void* operator_new2(int size)
{
    return cMemMan_alloc(size, D_004A3E88, D_004A3E84, 0);
}
#endif

INCLUDE_ASM("bx/memman", cMemMan_alloc);

//100%
INCLUDE_ASM("bx/memman", operator_new__FUi);
#ifdef SKIP_ASM
void* cMemMan_alloc(unsigned int size);

void* operator_new(unsigned int size)
{
    return cMemMan_alloc(size);
}
#endif

extern void* D_00538B00[16];
extern "C" void MUTEX_lock(void* mutex);
extern "C" void MUTEX_unlock(void* mutex);
extern "C" void func_00319B48(void* ptr);

//100%
INCLUDE_ASM("bx/memman", operator_delete__FPi);
#ifdef SKIP_ASM
void operator_delete(int* ptr)
{
    MUTEX_lock(D_00538B00);
    func_00319B48(ptr);
    MUTEX_unlock(D_00538B00);
}
#endif

//100%
INCLUDE_ASM("bx/memman", cMemMan_free__FPv);
#ifdef SKIP_ASM
void cMemMan_free(void* ptr)
{
    MUTEX_lock(D_00538B00);
    func_00319B48(ptr);
    MUTEX_unlock(D_00538B00);
}
#endif
