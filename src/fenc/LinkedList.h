#ifndef _INCLUDED_LINKEDLIST
#define _INCLUDED_LINKEDLIST

typedef void LinkedList;

LinkedList * LinkedList_malloc();

int64 LinkedList_insert(LinkedList * self, int64 value);

int64 LinkedList_insertAtIndex(LinkedList * self, int index, int64 value);

boolean LinkedList_isEmpty(LinkedList * self);

// remove the last element
int64 LinkedList_remove(LinkedList * self);

#endif
