#ifndef _INCLUDED_LINKEDLIST
#define _INCLUDED_LINKEDLIST

// doubly linked list with head node
typedef struct LinkedList LinkedList;

LinkedList * LinkedList_malloc();

void LinkedList_free(LinkedList * self);

void LinkedList_insert(LinkedList * self, int64 value);

void LinkedList_insertAtIndex(LinkedList * self, int index, int64 value);

boolean LinkedList_isEmpty(LinkedList * self);

// remove the last element
int64 LinkedList_remove(LinkedList * self);

int LinkedList_size(LinkedList * self);

#endif
