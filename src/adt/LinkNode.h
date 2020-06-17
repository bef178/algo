#ifndef _INCLUDED_LINKNODE
#define _INCLUDED_LINKNODE

typedef struct LinkNode {
    union {
        struct LinkNode * next;
        struct LinkNode * r;
    };
    union {
        struct LinkNode * prev;
        struct LinkNode * l;
    };
    int64 value;
} LinkNode;

LinkNode * LinkNode_malloc(int64 value);

void LinkNode_free(LinkNode * self);

void LinkNode_enlinkNext(LinkNode * self, LinkNode * futureNext);

LinkNode * LinkNode_delinkNext(LinkNode * self);

void LinkNode_insertNext(LinkNode * self, LinkNode * futureNext);

LinkNode * LinkNode_removeNext(LinkNode * self);

#endif // _INCLUDED_LINKNODE
