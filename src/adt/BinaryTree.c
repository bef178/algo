#include <stdlib.h>

typedef struct BinaryTree {
    BinaryTreeNode * root;
} BinaryTree;

BinaryTree * BinaryTree_malloc() {
    return calloc(1, sizeof(BinaryTree));
}

static void free1(BinaryTreeNode * self) {
    if (self == NULL) {
        return;
    }
    free1(self->l);
    free1(self->r);
    free(self);
}

void BinaryTree_free(BinaryTree * self) {
    free1(self->root);
    free(self);
}

void BinaryTree_setRoot(BinaryTree * self, BinaryTreeNode * root) {
    self->root = root;
}

static int depth(BinaryTreeNode * self) {
    if (self == NULL) {
        return 0;
    }
    int depthL = depth(self->l);
    int depthR = depth(self->r);
    return (depthL >= depthR ? depthL : depthR) + 1;
}

int BinaryTree_depth(BinaryTree * self) {
    return depth(self->root);
}
