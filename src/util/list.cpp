#include "common.h"

struct cListNode {
    cListNode* next; // 0x0
    cListNode* prev; // 0x4
};

struct cList {
    char pad_0x00[0x4];
    cListNode* head; // 0x4
    char pad_0x08[0x4];
    cListNode* tail; // 0xC
};

//100%
INCLUDE_ASM("util/list", cListNode_isSentinel__FP9cListNode);
#ifdef SKIP_ASM
int cListNode_isSentinel(cListNode* node)
{
    return (node->prev == node) || (node->next == node);
}
#endif

INCLUDE_ASM("util/list", cListNode_removeFromList);

INCLUDE_ASM("util/list", func_00397788);

INCLUDE_ASM("util/list", func_003977B8);

INCLUDE_ASM("util/list", func_003977E8);

//100%
INCLUDE_ASM("util/list", cList_first__FP5cList);
#ifdef SKIP_ASM
cListNode* cList_first(cList* list)
{
    cListNode* head = list->head;
    return (head->prev == head) ? 0 : head;
}
#endif

INCLUDE_ASM("util/list", func_00397870);

//100%
INCLUDE_ASM("util/list", cList_addToFront__FP5cListP9cListNode);
#ifdef SKIP_ASM
void cList_addToFront(cList* list, cListNode* newNode)
{
    cListNode* head = list->head;
    newNode->prev = head;
    newNode->next = head->next;
    head->next = newNode;
    list->head = newNode;
}
#endif

//100%
INCLUDE_ASM("util/list", cList_addToEnd__FP5cListP9cListNode);
#ifdef SKIP_ASM
void cList_addToEnd(cList* list, cListNode* newNode)
{
    cListNode* tail = list->tail;
    newNode->next = tail;
    newNode->prev = tail->prev;
    tail->prev = newNode;
    list->tail = newNode;
}
#endif

//79.33%
INCLUDE_ASM("util/list", func_00397930__FPv);
#ifdef SKIP_ASM
void* func_00397930(void* self)
{
    void* t0 = (char*)self + 0xc;
    *(int*)self = (int)self;
    *(int*)((char*)self + 0x10) = (int)t0;
    *(int*)((char*)self + 0x4) = (int)t0;
    *(int*)((char*)self + 0xc) = (int)self;
    return t0;
}
#endif

INCLUDE_ASM("util/list", func_00397948);

INCLUDE_ASM("util/list", func_003979C0);

INCLUDE_ASM("util/list", func_003979F8);

INCLUDE_ASM("util/list", func_00397A68);

