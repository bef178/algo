#ifndef _INCLUDED_ITERATOR
#define _INCLUDED_ITERATOR

#include "LinkNode.h"

typedef struct Iterator {
    LinkNode * head;
    LinkNode * current;
} Iterator;

Iterator * Iterator_malloc();

void Iterator_free(Iterator *);

boolean Iterator_hasNext(Iterator *);

int64 Iterator_next(Iterator *);

#endif // _INCLUDED_ITERATOR
