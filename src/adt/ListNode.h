#ifndef _INCLUDED_LISTNODE
#define _INCLUDED_LISTNODE

typedef struct ListNode ListNode;

ListNode * ListNode_malloc(int64 malloc);

void ListNode_free(ListNode * self);

ListNode * ListNode_delinkNext(ListNode * self);

void ListNode_enlinkNext(ListNode * self, ListNode * futureNext);

void ListNode_insertNext(ListNode * self, ListNode * futureNext);

ListNode * ListNode_removeNext(ListNode * self);

ListNode * ListNode_offset(ListNode * self, int offset);

int64 ListNode_get(ListNode * self);

void ListNode_set(ListNode * self, int64 value);

#endif
