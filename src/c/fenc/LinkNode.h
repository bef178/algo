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

#endif // _INCLUDED_LINKNODE
