#include <stdio.h>
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

int BinaryTreeNode_level(BinaryTreeNode * self) {
    int level = -1;
    for (BinaryTreeNode * p = self; p != null; p = p->parent) {
        level++;
    }
    return level;
}

void BinaryTreeNode_print(BinaryTreeNode * self) {
    if (self == NULL) {
        return;
    }
    printf("%ld:", self->value);
    if (self->l == NULL) {
        printf("?,");
    } else {
        printf("%ld,", self->l->value);
    }
    if (self->r == NULL) {
        printf("?");
    } else {
        printf("%ld", self->r->value);
    }
    printf("\n");
}

////////

void BinaryTree_free(BinaryTreeNode * root) {
    if (root != NULL) {
        BinaryTree_free(root->l);
        BinaryTree_free(root->r);
        BinaryTreeNode_free(root);
    }
}

int BinaryTree_depth(BinaryTreeNode * root) {
    if (root == NULL) {
        return -1;
    }
    int l = BinaryTree_depth(root->l);
    int r = BinaryTree_depth(root->r);
    return (l >= r ? l : r) + 1;
}

void BinaryTree_print(BinaryTreeNode * root) {
    if (root != NULL) {
        BinaryTreeNode_print(root);
        BinaryTree_print(root->l);
        BinaryTree_print(root->r);
    }
}
