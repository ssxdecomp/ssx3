#include "common.h"

struct sSplinePoint {
    char pad_0x00[0xC];
    float field_0xC;
    char pad_0x10[0x64 - 0x10];
    sSplinePoint* next; // 0x64
    char pad_0x68[0x84 - 0x68];
    float field_0x84;
};

struct sSplineHeader {
    char pad_0x00[0x20];
    int numPoints; // 0x20
    sSplinePoint* first; // 0x24
};

struct sSplineNode {
    char pad_0x00[0x68];
    sSplineHeader* header; // 0x68
};

struct cSpline {
    char pad_0x00[0x8];
    sSplineNode* node; // 0x8
};

//81.47% - condition/branch shape (slt-vs-slti, speculative float load in delay slot) not reproduced
INCLUDE_ASM("object/spline3d", cSpline_calcLength__FP7cSpline);
#ifdef SKIP_ASM
float cSpline_calcLength(cSpline* self)
{
    sSplineNode* node = self->node;
    sSplinePoint* cur = (sSplinePoint*)node->header;
    int count = node->header->numPoints;
    if (1 < count) {
        cur = node->header->first;
        int i = count - 1;
        do {
            i--;
            cur = cur->next;
        } while (i != 0);
    }
    return cur->field_0xC + cur->field_0x84;
}
#endif

INCLUDE_ASM("object/spline3d", func_00345538);

INCLUDE_ASM("object/spline3d", cSpline_readFromReplayFrame);

INCLUDE_ASM("object/spline3d", func_00345638);

