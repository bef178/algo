#include <assert.h>

void BinarySearchTree_add(BinaryTreeNode * root, int64 value) {
    assert(root != NULL);
    if (value < root->value) {
        if (root->l == NULL) {
            root->l = BinaryTreeNode_malloc(value);
        } else {
            BinarySearchTree_add(root->l, value);
        }
    } else {
        if (root->r == NULL) {
            root->r = BinaryTreeNode_malloc(value);
        } else {
            BinarySearchTree_add(root->r, value);
        }
    }
}
