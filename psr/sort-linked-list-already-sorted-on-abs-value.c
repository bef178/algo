/**
 * Given a singly linked list which is already sorted on abs value, sort it on value
 *
 * leetcode #2046 medium
 * https://leetcode.com/problems/sort-linked-list-already-sorted-using-absolute-values/
 *
 * 正序或逆序解法类似。以双正序为例，取出负数加入链首即可。
 * 1,-2,3,4,-5,-6 => -6,-5,-2,1,3,4
 */

#include <stdlib.h>

LinkedListNode * sort(LinkedListNode * head) {
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

LinkedListNode * sort2(LinkedListNode * head) {
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
