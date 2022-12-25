#ifndef _INCLUDED_BINARYTREENODE
#define _INCLUDED_BINARYTREENODE

#include "LinkNode.h"

typedef LinkNode BinaryTreeNode;

BinaryTreeNode * BinaryTreeNode_malloc();

BinaryTreeNode * BinaryTreeNode_wrapValue(int64 value);

int64 BinaryTreeNode_free(BinaryTreeNode * self);

#endif // _INCLUDED_BINARYTREENODE
