#include <assert.h>
#include <stdlib.h>

public
LinkNode * LinkNode_malloc(int64 value) {
    LinkNode * node = calloc(1, sizeof(LinkNode));
    node->value = value;
    return node;
}

public
void LinkNode_free(LinkNode * self) {
    free(self);
}

/**
 * concat/join
 */
public
void LinkNode_enlinkNext(LinkNode * self, LinkNode * futureNext) {
    self->next = futureNext;
    if (futureNext != NULL) {
        futureNext->prev = self;
    }
}

public
LinkNode * LinkNode_delinkNext(LinkNode * self) {
    LinkNode * p = self->next;
    if (p != NULL) {
        self->next = NULL;
        p->prev = NULL;
    }
    return p;
}

public
void LinkNode_insertNext(LinkNode * self, LinkNode * futureNext) {
    assert(futureNext != NULL);
    LinkNode * p = LinkNode_delinkNext(self);
    LinkNode_enlinkNext(self, futureNext);
    LinkNode_enlinkNext(futureNext, p);
}

public
LinkNode * LinkNode_removeNext(LinkNode * self) {
    LinkNode * p = LinkNode_delinkNext(self);
    if (p != NULL) {
        LinkNode_enlinkNext(self, LinkNode_delinkNext(p));
    }
    return p;
}
