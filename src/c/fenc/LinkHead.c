/**
 * TODO there should be a fore-most processor:
 *  x. generate .public.h/.internal.h file
 *      x. include-guard
 *      x. forward declaration of function
 *      x. public macro/struct/variable
 *      x. related comments
 *  x. generate .c file
 *      x. remove interface macro/typedef
 *      x. add forward declaration of non-interface function
 */

/**
 * LinkHead
 * see list_head in Linux kernel
 */

public
#define MEMBER_OFFSET(__structType, __memberName)   \
    (word) &(((__structType *) 0)->__memberName)

public
#define GET_CONTAINER(__structType, __memberName, __memberAddr)    \
    (__structType *)((word) (__memberAddr) - MEMBER_OFFSET(__structType, __memberName))

public
#define CAST(__addr, __type)    \
    *((__type *) (__addr))

public
typedef struct LinkHead {
    struct LinkHead * next;
    struct LinkHead * prev;
} LinkHead;

#include <assert.h>
#include <stdlib.h>

public
LinkHead * LinkHead_malloc() {
    return calloc(1, sizeof(LinkHead));
}

public
void LinkHead_free(LinkHead * self) {
    free(self);
}

public
void LinkHead_enlinkNext(LinkHead * self, LinkHead * futureNext) {
    // assert(self != NULL);
    self->next = futureNext;
    if (futureNext != NULL) {
        futureNext->prev = self;
    }
}

/**
 * return delinked node
 */
public
LinkHead * LinkHead_delinkNext(LinkHead * self) {
    LinkHead * p = self->next;
    if (p != NULL) {
        self->next = NULL;
        p->prev = NULL;
    }
    return p;
}

public
void LinkHead_insertNext(LinkHead * self, LinkHead * futureNext) {
    assert(futureNext != NULL);
    LinkHead * p = LinkHead_delinkNext(self);
    LinkHead_enlinkNext(self, futureNext);
    LinkHead_enlinkNext(futureNext, p);
}

/**
 * return removed node
 */
public
LinkHead * LinkHead_removeNext(LinkHead * self) {
    LinkHead * p = self->next;
    if (p != NULL) {
        LinkHead_enlinkNext(self, LinkHead_delinkNext(p));
    }
    return p;
}
