#include "common.h"

void operator_delete(int* ptr);

struct sTriggerNode {
    void* pad;
    sTriggerNode* next;
};

struct cActiveTriggerList {
    sTriggerNode* head;
};

INCLUDE_ASM("camera/trigger/triggeralgorithms", cActiveTriggerList_purge__FP18cActiveTriggerList);
#ifdef SKIP_ASM
void cActiveTriggerList_purge(cActiveTriggerList* self)
{
    sTriggerNode* node = self->head;
    if (node != 0) {
        do {
            sTriggerNode* next = node->next;
            operator_delete((int*)node);
            node = next;
        } while (node != 0);
    }
    self->head = 0;
}
#endif

INCLUDE_ASM("camera/trigger/triggeralgorithms", func_0016C678);

INCLUDE_ASM("camera/trigger/triggeralgorithms", func_0016C6B0);

INCLUDE_ASM("camera/trigger/triggeralgorithms", func_0016C6E0);

INCLUDE_ASM("camera/trigger/triggeralgorithms", cActiveTriggerList_add);

INCLUDE_ASM("camera/trigger/triggeralgorithms", func_0016C778);

INCLUDE_ASM("camera/trigger/triggeralgorithms", func_0016C800);

INCLUDE_ASM("camera/trigger/triggeralgorithms", func_0016C888);

INCLUDE_ASM("camera/trigger/triggeralgorithms", func_0016C918);

INCLUDE_ASM("camera/trigger/triggeralgorithms", func_0016C968);

