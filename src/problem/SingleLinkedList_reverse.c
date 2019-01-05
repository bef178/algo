/**
 * 单链表原地逆序
 *
 * 注意考虑环链
 */

#include <stdlib.h>

ListHead * SingleLinkedList_reverse(ListHead * p) {
    if (p == NULL) {
        return NULL;
    }

    ListHead * newHead = p;
    p = p->next;
    newHead->next = NULL;
    ListHead * newTail = newHead;

    while (p != NULL && p != newTail) {
        ListHead * q = p;
        p = p->next;
        q->next = newHead;
        newHead = q;
    }
    if (p == newTail) {
        // cyclic
        newTail->next = newHead;
    }
    return newHead;
}
