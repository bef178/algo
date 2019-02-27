#ifndef _INCLUDED_LISTNODE
#define _INCLUDED_LISTNODE

typedef struct ListNode {
    struct ListNode * next;
    struct ListNode * prev;
    int64 value;
} ListNode;

ListNode * ListNode_malloc(int64 value);

void ListNode_free(ListNode * self);

void ListNode_enlinkNext(ListNode * self, ListNode * futureNext);

ListNode * ListNode_delinkNext(ListNode * self);

void ListNode_insertNext(ListNode * self, ListNode * futureNext);

ListNode * ListNode_removeNext(ListNode * self);

#endif // _INCLUDED_LISTNODE
