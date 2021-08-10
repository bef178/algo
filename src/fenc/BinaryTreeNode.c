#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

public
BinaryTreeNode * BinaryTreeNode_malloc() {
    BinaryTreeNode * node = calloc(1, sizeof(BinaryTreeNode));
    node->value = 0;
    return node;
}

public
BinaryTreeNode * BinaryTreeNode_wrapValue(int64 value) {
    BinaryTreeNode * node = BinaryTreeNode_malloc();
    node->value = value;
    return node;
}

public
int64 BinaryTreeNode_free(BinaryTreeNode * self) {
    int64 value = self->value;
    free(self);
    return value;
}
