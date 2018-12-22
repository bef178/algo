#ifndef _INCLUDED_BINARYTREE
#define _INCLUDED_BINARYTREE

#include "BinaryTreeNode.h"

typedef struct BinaryTree BinaryTree;

BinaryTree * BinaryTree_malloc();

void BinaryTree_free(BinaryTree * self);

void BinaryTree_setRoot(BinaryTree * self, BinaryTreeNode * root);

int BinaryTree_depth(BinaryTree * self);

#endif
