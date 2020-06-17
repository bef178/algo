/**
 * sort a single linked list which is already sorted by abs value non-increasingly
 */

#include <stdlib.h>

LinkNode * LinkedList_sortAbsNonInc(LinkNode * head) {
    if (head == NULL) {
        return head;
    }

    LinkNode * pivot = NULL; // points to the last positive node
    while (head != NULL) {
        LinkNode * p = head;
        head = head->next;
        p->next = pivot;
        pivot = p;
        if (pivot->value >= 0) {
            break;
        }
    }
    if (head == NULL) {
        return pivot;
    }
    LinkNode * newHead = pivot;
    while (head != NULL) {
        LinkNode * p = head;
        head = head->next;
        p->next = pivot->next;
        pivot->next = p;
        if (pivot->next->value >= 0) {
            pivot = pivot->next;
        }
    }
    return newHead;
}

LinkNode * LinkedList_sortAbsNonInc2(LinkNode * head) {
    if (head == NULL) {
        return NULL;
    }

    // with head node
    LinkNode * tmpHead = LinkNode_malloc(0);
    LinkNode_enlinkNext(tmpHead, head);

    LinkNode * negHead = NULL;

    head = tmpHead;
    while (head->next != NULL) {
        if (head->next->value < 0) {
            LinkNode * p = LinkNode_removeNext(head);
            LinkNode_insertNext(p, negHead);
            negHead = p;
        }
    }
    LinkNode_enlinkNext(head, negHead);
    head = LinkNode_delinkNext(tmpHead);
    free(tmpHead);
    return head;
}

// 5, -5, 5*, -5*, 4, 3, -2
// 5, 4, 3, 2
// -5, -4, -3, -2
