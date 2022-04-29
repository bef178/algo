/**
 * 单链表原地逆序
 *
 * 注意环链

 * leetcode #206 easy
 * https://leetcode.com/problems/reverse-linked-list/
 */

#include <stdlib.h>

LinkNode * reverseLinkedList(LinkNode * p) {
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
