/**
 * List works base on index
 * accepting only non-null value
 */

#ifndef _INCLUDED_LISTNODE
#define _INCLUDED_LISTNODE

typedef struct ListNode {
    ListHead linkage;
    void * value;
} ListNode;

ListNode * ListNode_malloc();

void ListNode_free(ListNode * self);

ListNode * ListNode_fromListHead(ListHead * head);

ListNode * ListNode_offset(ListNode * self, int offset);

#endif
