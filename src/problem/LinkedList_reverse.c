/**
 * 单链表原地逆序
 *
 * 注意考虑环链
 */

#include <stdlib.h>

LinkNode * LinkedList_reverse(LinkNode * p) {
    if (p == NULL) {
        return NULL;
    }

    LinkNode * newHead = p;
    p = p->next;
    newHead->next = NULL;
    LinkNode * newTail = newHead;

    while (p != NULL && p != newTail) {
        LinkNode * q = p;
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
