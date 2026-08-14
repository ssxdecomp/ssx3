#include "common.h"

struct cWorldViewSectionList {
    char pad_0x00[0x8];
    int mNumSections; // 0x8
};

struct cWorldView {
    char pad_0x00[0x4];
    cWorldViewSectionList* mSections; // 0x4
};

//100%
INCLUDE_ASM("world/worldview", cWorldView_getNumSections__FP10cWorldView);
#ifdef SKIP_ASM
int cWorldView_getNumSections(cWorldView* self)
{
    if (self->mSections == 0) {
        return 0;
    }
    return self->mSections->mNumSections;
}
#endif

INCLUDE_ASM("world/worldview", func_003A9820);

struct cWorldViewEntry {
    char pad_0x00[0x14];
    int field_0x14;
};

//100%
INCLUDE_ASM("world/worldview", cWorldView_isSectionLoaded__FP10cWorldViewi);
#ifdef SKIP_ASM
int cWorldView_isSectionLoaded(cWorldView* self, int section)
{
    if (self->mSections == 0 || (unsigned int)section >= (unsigned int)self->mSections->mNumSections) {
        return 0;
    }
    cWorldViewEntry* entry = (cWorldViewEntry*)((char*)self + section * 8);
    return (unsigned int)(entry->field_0x14 - 5) < 2;
}
#endif

INCLUDE_ASM("world/worldview", func_003A9890);

INCLUDE_ASM("world/worldview", func_003A98C8);

INCLUDE_ASM("world/worldview", func_003A9958);

INCLUDE_ASM("world/worldview", func_003A99D8);

//100%
INCLUDE_ASM("world/worldview", func_003A9A98);
#ifdef SKIP_ASM
extern "C" void* func_003A9A98(void* self, int a1)
{
    return (char*)(*(void**)((char*)self + 0x10)) + a1 * 0x44;
}
#endif

//100%
INCLUDE_ASM("world/worldview", func_003A9AB0__FPv);
#ifdef SKIP_ASM
int func_003A9AB0(void* self)
{
    return *(int*)((char*)*(void**)((char*)self + 0x4) + 0x10);
}
#endif

INCLUDE_ASM("world/worldview", func_003A9D60);

INCLUDE_ASM("world/worldview", func_003A9E50);

INCLUDE_ASM("world/worldview", func_003AA028);

INCLUDE_ASM("world/worldview", func_003AA2F0);

INCLUDE_ASM("world/worldview", func_003AA3F0);

INCLUDE_ASM("world/worldview", func_003AA438);

INCLUDE_ASM("world/worldview", func_003AA520);

INCLUDE_ASM("world/worldview", func_003AA5C8);

INCLUDE_ASM("world/worldview", func_003AA608);

//100%
INCLUDE_ASM("world/worldview", func_003AA6E8);
#ifdef SKIP_ASM
extern "C" int func_003AA6E8(void* self, void* a1)
{
    *(int*)((char*)a1 + 0x20) += (int)a1;
    return 1;
}
#endif

INCLUDE_ASM("world/worldview", func_003AA700);

INCLUDE_ASM("world/worldview", func_003AA758);

INCLUDE_ASM("world/worldview", func_003AA780);

INCLUDE_ASM("world/worldview", func_003AA830);

//100%
INCLUDE_ASM("world/worldview", func_003AA8D8);
#ifdef SKIP_ASM
extern "C" int func_003AA8D8(void* self, void* a1, int a2)
{
    *(int*)((char*)a1 + 0x4) += a2;
    return 1;
}
#endif

INCLUDE_ASM("world/worldview", func_003AA8F0);

INCLUDE_ASM("world/worldview", func_003AA960);

INCLUDE_ASM("world/worldview", func_003AAA08);

INCLUDE_ASM("world/worldview", func_003AABD8);

INCLUDE_ASM("world/worldview", func_003AAC50);

INCLUDE_ASM("world/worldview", func_003AACA8);

INCLUDE_ASM("world/worldview", func_003AAD98);

INCLUDE_ASM("world/worldview", func_003AADE8);

INCLUDE_ASM("world/worldview", func_003AAE40);

//100%
INCLUDE_ASM("world/worldview", func_003AAE60__FPv);
#ifdef SKIP_ASM
void func_003AAE60(void* self)
{
}
#endif

INCLUDE_ASM("world/worldview", func_003AAE68);

INCLUDE_ASM("world/worldview", func_003AB498);

INCLUDE_ASM("world/worldview", func_003ABE40);

INCLUDE_ASM("world/worldview", func_003ABF20);

INCLUDE_ASM("world/worldview", func_003ABF50);

INCLUDE_ASM("world/worldview", func_003ABFC0);

INCLUDE_ASM("world/worldview", func_003AC048);

INCLUDE_ASM("world/worldview", func_003AC2A8);

INCLUDE_ASM("world/worldview", func_003AC358);

INCLUDE_ASM("world/worldview", func_003AC508);

INCLUDE_ASM("world/worldview", func_003AC7C8);

