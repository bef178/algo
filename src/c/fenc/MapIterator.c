#include <assert.h>
#include <stdlib.h>

void MapIterator_free(MapIterator * self) {
    Iterator * it = (Iterator *) self;
    while (it->head->next != NULL) {
        LinkedListNode * p = LinkedListNode_removeNext(it->head);
        MapEntry * entry = (void *) p->value;
        MapEntry_free(entry);
        LinkedListNode_free(p);
    }
    Iterator_free(it);
}

boolean MapIterator_hasNext(MapIterator * self) {
    return Iterator_hasNext((Iterator *) self);
}

MapEntry * MapIterator_next(MapIterator * self) {
    return (void *) Iterator_next((Iterator *) self);
}
