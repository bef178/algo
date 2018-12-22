#include <stdlib.h>

BinaryTreeNode * BinaryTreeNode_malloc(int64 value) {
    BinaryTreeNode * p = calloc(1, sizeof(BinaryTreeNode));
    p->value = value;
    return p;
}

void BinaryTreeNode_free(BinaryTreeNode * self) {
    free(self);
}

static BinaryTreeNode * delinkL(BinaryTreeNode * self) {
    BinaryTreeNode * delinked = self->l;
    if (delinked != NULL) {
        self->l = NULL;
        delinked->parent = NULL;
    }
    return delinked;
}

static BinaryTreeNode * delinkR(BinaryTreeNode * self) {
    BinaryTreeNode * delinked = self->r;
    if (delinked != NULL) {
        self->r = NULL;
        delinked->parent = NULL;
    }
    return delinked;
}

void BinaryTreeNode_enlinkL(BinaryTreeNode * self,
        BinaryTreeNode * futureNode) {
    // assert self->r == null;
    // assert futureNode == null || futureNode->parent == null;
    self->l = futureNode;
    if (futureNode != NULL) {
        futureNode->parent = self;
    }
}

void BinaryTreeNode_enlinkR(BinaryTreeNode * self,
        BinaryTreeNode * futureNode) {
    // assert self->r == null;
    // assert futureNode == null || futureNode->parent == null;
    self->r = futureNode;
    if (futureNode != NULL) {
        futureNode->parent = self;
    }
}
