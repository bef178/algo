#ifndef _INCLUDED_BINARYTREE
#define _INCLUDED_BINARYTREE

#include "LinkNode.h"

typedef LinkNode BinaryTreeNode;

extern BinaryTreeNode * (*BinaryTreeNode_malloc)(int64);

void BinaryTree_free(LinkNode * root);

int BinaryTree_depth(LinkNode * root);

int BinaryTree_getNodeLevel(LinkNode * root, LinkNode * node);

void BinaryTree_print(LinkNode * root);

#endif // _INCLUDED_BINARYTREE
