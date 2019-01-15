/**
 * sort a single linked list which is already sorted by abs value non-increasingly
 */

#include <stdlib.h>

static ListNode * sortAbsNonIncreasinglyList(ListNode * head) {
    if (head == NULL) {
        return head;
    }

    ListNode * pivot = NULL; // points to the last positive node
    while (head != NULL) {
        ListNode * p = head;
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
    ListNode * newHead = pivot;
    while (head != NULL) {
        ListNode * p = head;
        head = head->next;
        p->next = pivot->next;
        pivot->next = p;
        if (pivot->next->value >= 0) {
            pivot = pivot->next;
        }
    }
    return newHead;
}

static ListNode * sortAbsNonIncreasinglyList2(ListNode * head) {
    if (head == NULL) {
        return NULL;
    }

    // with head node
    ListNode * tmpHead = ListNode_malloc(0);
    ListNode_enlinkNext(tmpHead, head);

    ListNode * negHead = NULL;

    head = tmpHead;
    while (head->next != NULL) {
        if (head->next->value < 0) {
            ListNode * p = ListNode_removeNext(head);
            ListNode_insertNext(p, negHead);
            negHead = p;
        }
    }
    ListNode_enlinkNext(head, negHead);
    head = ListNode_delinkNext(tmpHead);
    free(tmpHead);
    return head;
}

// 5, -5, 5*, -5*, 4, 3, -2
// 5, 4, 3, 2
// -5, -4, -3, -2
void testSortAbsNonIncreasinglyList() {
}
