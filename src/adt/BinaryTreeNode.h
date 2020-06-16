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

/**
 * the distance to the root
 * null => -1
 * root => 0
 */
int BinaryTreeNode_level(BinaryTreeNode * self);

void BinaryTreeNode_print(BinaryTreeNode * self);

////////

void BinaryTree_free(BinaryTreeNode * root);

/**
 * the max distance between the root and a leaf
 * empty tree depth = -1
 */
int BinaryTree_depth(BinaryTreeNode * root);

void BinaryTree_print(BinaryTreeNode * root);

#endif // _INCLUDED_BINARYTREENODE
