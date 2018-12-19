/**
 * TODO should compose a very fore-most processor:
 *  1. create header file
 *      x. include-guard
 *      x. add forward declaration of public macro/struct/variable/function
 *      x. relevant comments
 *  2. modify current .c file
 *      x. remove interface macro/typedef
 *      x. add forward declaration of non-interface function
 */

#include <stdlib.h>

ListHead * ListHead_malloc() {
    return (ListHead *) calloc(1, sizeof(ListHead));
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

ListHead * ListHead_delinkNext(ListHead * self) {
    ListHead * ofNext = self->next;
    if (ofNext != NULL) {
        self->next = NULL;
        ofNext->prev = NULL;
    }
    return ofNext;
}

void ListHead_insertNext(ListHead * self, ListHead * futureNext) {
    // assert futureNext != null;
    ListHead * ofNext = ListHead_delinkNext(self);
    ListHead_enlinkNext(self, futureNext);
    ListHead_enlinkNext(futureNext, ofNext);
}

ListHead * ListHead_removeNext(ListHead * self) {
    ListHead * ofNext = self->next;
    if (ofNext != NULL) {
        ListHead_enlinkNext(self, ListHead_delinkNext(ofNext));
    }
    return ofNext;
}

ListHead * ListHead_offset(ListHead * self, int offset) {
    ListHead * p = self;
    if (offset >= 0) {
        while (offset-- > 0 && p != NULL) {
            p = p->next;
        }
    } else {
        while (offset++ < 0 && p != NULL) {
            p = p->prev;
        }
    }
    return p;
}
