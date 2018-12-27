#ifndef _INCLUDED_BINARYTREENODE
#define _INCLUDED_BINARYTREENODE

typedef struct BinaryTreeNode {
    struct BinaryTreeNode * parent;
    struct BinaryTreeNode * r;
    struct BinaryTreeNode * l;
    int64 value;
} BinaryTreeNode;

BinaryTreeNode * BinaryTreeNode_malloc(int64 value);

void BinaryTreeNode_free(BinaryTreeNode * self);

void BinaryTreeNode_enlinkL(BinaryTreeNode * self, BinaryTreeNode * futureNode);

void BinaryTreeNode_enlinkR(BinaryTreeNode * self, BinaryTreeNode * futureNode);

void BinaryTreeNode_print(BinaryTreeNode * self);

#endif // _INCLUDED_BINARYTREENODE
