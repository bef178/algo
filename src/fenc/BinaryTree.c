#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

public
void BinaryTree_free(BinaryTreeNode * root) {
    if (root != NULL) {
        BinaryTree_free(root->l);
        BinaryTree_free(root->r);
        BinaryTreeNode_free(root);
    }
}

public
int BinaryTree_size(BinaryTreeNode * root) {
    if (root == NULL) {
        return 0;
    }
    return BinaryTree_size(root->l) + 1 + BinaryTree_size(root->r);
}

/**
 * the max distance between the root and a leaf
 * empty tree depth = -1
 */
public
int BinaryTree_depth(BinaryTreeNode * root) {
    if (root == NULL) {
        return -1;
    }
    int l = BinaryTree_depth(root->l);
    int r = BinaryTree_depth(root->r);
    return (l >= r ? l : r) + 1;
}

/**
 * the distance to the root
 * null => -1
 * root => 0
 */
public
int BinaryTree_getNodeLevel(BinaryTreeNode * root, BinaryTreeNode * node) {
    assert(node != NULL);

    if (root == NULL) {
        return -1;
    } else if (root == node) {
        return 0;
    }

    int level = BinaryTree_getNodeLevel(root->l, node);
    if (level >= 0) {
        return level + 1;
    }
    level = BinaryTree_getNodeLevel(root->r, node);
    if (level >= 0) {
        return level + 1;
    }
    return -1;
}

public
void BinaryTree_print(BinaryTreeNode * root) {
    if (root == NULL) {
        printf("?\n");
        return;
    }

    printf("%ld:", root->value);
    if (root->l == NULL) {
        printf("?");
    } else {
        printf("%ld", root->l->value);
    }
    printf(",");
    if (root->r == NULL) {
        printf("?");
    } else {
        printf("%ld", root->r->value);
    }
    printf("\n");

    BinaryTree_print(root->l);
    BinaryTree_print(root->r);
}
