#ifndef _INCLUDED_LIST
#define _INCLUDED_LIST

typedef struct List List;

List * List_malloc();

void List_free(List * self);

void List_clear(List * self);

int List_size(List * self);

boolean List_isEmpty(List * self);

void * List_get(List * self, int index);

void * List_set(List * self, int index, void * value);

void List_insert(List * self, int index, void * value);

void * List_remove(List * self, int index);

int List_indexOf(List * self, int start, void * value, compare_f * compare);

#endif // _INCLUDED_LIST
