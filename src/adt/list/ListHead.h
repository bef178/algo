#ifndef _INCLUDED_LINKHEAD
#define _INCLUDED_LINKHEAD

#define MEMBER_OFFSET(__structType, __memberName)   \
    (word) &(((__structType *) 0)->__memberName)

#define GET_CONTAINER(__structType, __memberName, __memberAddr)    \
    (__structType *)((word) (__memberAddr) - MEMBER_OFFSET(__structType, __memberName))

#define MEMBER_SET(__structType, __structAddr, __memberType, __memberName, __memberValue) \
    *(__memberType *) ((word *) __structAddr + MEMBER_OFFSET(__structType, __memberName)) = __memberValue;



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

ListHead * ListHead_offset(ListHead * self, int offset);

#endif // _INCLUDED_LINKHEAD
