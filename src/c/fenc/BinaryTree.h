#ifndef _INCLUDED_BINARYTREE
#define _INCLUDED_BINARYTREE

#include "BinaryTreeNode.h"

void BinaryTree_free(BinaryTreeNode * root);

int BinaryTree_size(BinaryTreeNode * root);

boolean BinaryTree_containsNode(BinaryTreeNode * root, BinaryTreeNode * node);

int BinaryTree_depth(BinaryTreeNode * root);

int BinaryTree_getNodeLevel(BinaryTreeNode * root, BinaryTreeNode * node);

void BinaryTree_print(BinaryTreeNode * root);

#endif // _INCLUDED_BINARYTREE
