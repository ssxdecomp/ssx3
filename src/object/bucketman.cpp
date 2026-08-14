#include "common.h"

struct cBucketMan {
    char pad_0x00[0x4];
    char* mBuckets; // 0x4, element size 0x44
};

INCLUDE_ASM("object/bucketman", cBucketMan_init);

INCLUDE_ASM("object/bucketman", func_00354B38);

INCLUDE_ASM("object/bucketman", cBucketMan_add);

INCLUDE_ASM("object/bucketman", func_00354C98);

INCLUDE_ASM("object/bucketman", func_00354E48);

//95%
INCLUDE_ASM("object/bucketman", cBucketMan_first__FP10cBucketMani);
#ifdef SKIP_ASM
void* cBucketMan_first(cBucketMan* self, int index)
{
    char* bucket = &self->mBuckets[index * 0x44];
    void* head = *(void**)(bucket + 0x8);
    return (head == (void*)(bucket + 0x14)) ? 0 : head;
}
#endif

INCLUDE_ASM("object/bucketman", func_00354ED0);

//100%
INCLUDE_ASM("object/bucketman", cBucketMan_next__FP10cBucketManPvi);
#ifdef SKIP_ASM
void* cBucketMan_next(cBucketMan* self, void* node, int index)
{
    char* bucket = self->mBuckets + index * 0x44;
    void* next = *(void**)((char*)node + 0x4);
    return (next == (void*)(bucket + 0x14)) ? 0 : next;
}
#endif

INCLUDE_ASM("object/bucketman", func_00354F20);

//95%
INCLUDE_ASM("object/bucketman", cBucketMan_addfirst__FP10cBucketMani);
#ifdef SKIP_ASM
void* cBucketMan_addfirst(cBucketMan* self, int index)
{
    index *= 0x44;
    char* bucket = self->mBuckets + index;
    void* head = *(void**)(bucket + 0x28);
    return (head == (void*)(bucket + 0x34)) ? 0 : head;
}
#endif

INCLUDE_ASM("object/bucketman", func_00354F70);

INCLUDE_ASM("object/bucketman", func_00354F98);

INCLUDE_ASM("object/bucketman", func_00355028);

INCLUDE_ASM("object/bucketman", func_003550A0);

INCLUDE_ASM("object/bucketman", cBucketMan_purgeBucket);

INCLUDE_ASM("object/bucketman", func_003551A8);

// 0x44-byte elements reached through a pointer at self+0x4
struct sBucketEntry {
    int flags;
    char pad_0x04[0x40];
};

//100%
INCLUDE_ASM("object/bucketman", func_00355260);
#ifdef SKIP_ASM
extern "C" void func_00355260(void* self, int a1)
{
    sBucketEntry* p = *(sBucketEntry**)((char*)self + 0x4);
    p[a1].flags |= 1;
}
#endif

INCLUDE_ASM("object/bucketman", func_00355280);

