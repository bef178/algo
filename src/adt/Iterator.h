#ifndef _INCLUDED_ITERATOR
#define _INCLUDED_ITERATOR

#include "ListNode.h"

typedef struct Iterator {
    ListNode * head;
    ListNode * current;
} Iterator;

Iterator * Iterator_malloc();

void Iterator_free(Iterator *);

boolean Iterator_hasNext(Iterator *);

int64 Iterator_next(Iterator *);

#endif // _INCLUDED_ITERATOR
