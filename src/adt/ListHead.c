/**
 * TODO there should be a fore-most processor:
 *  1. create header file
 *      x. include-guard
 *      x. add forward declaration of public macro/struct/variable/function
 *      x. relevant comments
 *  2. modify current .c file
 *      x. remove interface macro/typedef
 *      x. add forward declaration of non-interface function
 */

#include <assert.h>
#include <stdlib.h>

ListHead * ListHead_malloc() {
    return calloc(1, sizeof(ListHead));
}

void ListHead_free(ListHead * self) {
    free(self);
}

void ListHead_enlinkNext(ListHead * self, ListHead * futureNext) {
    // assert self->next == null;
    // assert futureNext == null || futureNext->prev == null;
    self->next = futureNext;
    if (futureNext != NULL) {
        futureNext->prev = self;
    }
}

/**
 * return delinked node
 */
ListHead * ListHead_delinkNext(ListHead * self) {
    ListHead * p = self->next;
    if (p != NULL) {
        self->next = NULL;
        p->prev = NULL;
    }
    return p;
}

void ListHead_insertNext(ListHead * self, ListHead * futureNext) {
    assert(futureNext != NULL);
    // assert futureNext->next == null && futureNext->prev == null;
    ListHead * p = ListHead_delinkNext(self);
    ListHead_enlinkNext(self, futureNext);
    ListHead_enlinkNext(futureNext, p);
}

/**
 * return removed node
 */
ListHead * ListHead_removeNext(ListHead * self) {
    ListHead * p = self->next;
    if (p != NULL) {
        ListHead_enlinkNext(self, ListHead_delinkNext(p));
    }
    return p;
}
