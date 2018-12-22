#ifndef _INCLUDED_LIST
#define _INCLUDED_LIST

typedef struct List List;

typedef int (List_comparef)(int64, int64);

List * List_malloc();

void List_free(List * self);

void List_clear(List * self);

int List_size(List * self);

boolean List_isEmpty(List * self);

int64 List_get(List * self, int index);

int64 List_set(List * self, int index, int64 value);

void List_insert(List * self, int index, int64 value);

int64 List_remove(List * self, int index);

int List_indexOf(List * self, int start, int64 value, List_comparef * compare);

#endif // _INCLUDED_LIST
