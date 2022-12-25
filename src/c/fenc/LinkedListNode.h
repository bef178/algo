#ifndef _INCLUDED_LINKEDLISTNODE
#define _INCLUDED_LINKEDLISTNODE

#include "LinkNode.h"

typedef LinkNode LinkedListNode;

LinkedListNode * LinkedListNode_malloc();

LinkedListNode * LinkedListNode_wrapValue(int64 value);

int64 LinkedListNode_free(LinkedListNode * self);

void LinkedListNode_enlinkNext(LinkedListNode * self, LinkedListNode * futureNext);

LinkedListNode * LinkedListNode_delinkNext(LinkedListNode * self);

void LinkedListNode_insertNext(LinkedListNode * self, LinkedListNode * futureNext);

LinkedListNode * LinkedListNode_removeNext(LinkedListNode * self);

#endif // _INCLUDED_LINKEDLISTNODE
