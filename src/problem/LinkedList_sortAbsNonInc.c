/**
 * sort a single linked list which is already sorted by abs value non-increasingly
 */

#include <stdlib.h>

LinkedListNode * LinkedList_sortAbsNonInc(LinkedListNode * head) {
    if (head == NULL) {
        return head;
    }

    LinkedListNode * pivot = NULL; // points to the last positive node
    while (head != NULL) {
        LinkedListNode * p = head;
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
    LinkedListNode * newHead = pivot;
    while (head != NULL) {
        LinkedListNode * p = head;
        head = head->next;
        p->next = pivot->next;
        pivot->next = p;
        if (pivot->next->value >= 0) {
            pivot = pivot->next;
        }
    }
    return newHead;
}

LinkedListNode * LinkedList_sortAbsNonInc2(LinkedListNode * head) {
    if (head == NULL) {
        return NULL;
    }

    // with head node
    LinkedListNode * tmpHead = LinkedListNode_malloc(0);
    LinkedListNode_enlinkNext(tmpHead, head);

    LinkedListNode * negHead = NULL;

    head = tmpHead;
    while (head->next != NULL) {
        if (head->next->value < 0) {
            LinkedListNode * p = LinkedListNode_removeNext(head);
            LinkedListNode_insertNext(p, negHead);
            negHead = p;
        }
    }
    LinkedListNode_enlinkNext(head, negHead);
    head = LinkedListNode_delinkNext(tmpHead);
    free(tmpHead);
    return head;
}

// 5, -5, 5*, -5*, 4, 3, -2
// 5, 4, 3, 2
// -5, -4, -3, -2
