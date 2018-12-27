#include <stdlib.h>

void BinaryTree_free(BinaryTreeNode * root) {
    if (root == NULL) {
        return;
    }
    BinaryTree_free(root->l);
    BinaryTree_free(root->r);
    BinaryTreeNode_free(root);
}

int BinaryTree_depth(BinaryTreeNode * root) {
    if (root == NULL) {
        return 0;
    }
    int depthL = BinaryTree_depth(root->l);
    int depthR = BinaryTree_depth(root->r);
    return (depthL >= depthR ? depthL : depthR) + 1;
}

void BinaryTree_print(BinaryTreeNode * root) {
    if (root == NULL) {
        return;
    }
    BinaryTreeNode_print(root);
    BinaryTree_print(root->l);
    BinaryTree_print(root->r);
}
