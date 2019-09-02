#ifndef _INCLUDED_LISTHEAD
#define _INCLUDED_LISTHEAD

#define MEMBER_OFFSET(__structType, __memberName)   \
    (word) &(((__structType *) 0)->__memberName)

#define GET_CONTAINER(__structType, __memberName, __memberAddr)    \
    (__structType *)((word) (__memberAddr) - MEMBER_OFFSET(__structType, __memberName))

#define CAST(__addr, __type)    \
    *((__type *) (__addr))

typedef struct ListHead {
    struct ListHead * next;
    struct ListHead * prev;
} ListHead;

ListHead * ListHead_malloc();

void ListHead_free(ListHead * self);

void ListHead_enlinkNext(ListHead * self, ListHead * futureNext);

ListHead * ListHead_delinkNext(ListHead * self);

void ListHead_insertNext(ListHead * self, ListHead * futureNext);

ListHead * ListHead_removeNext(ListHead * self);

#endif // _INCLUDED_LISTHEAD
