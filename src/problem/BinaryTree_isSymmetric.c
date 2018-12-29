static boolean isSymmetric(BinaryTreeNode * l, BinaryTreeNode * r) {
    if (l == NULL && r == NULL) {
        return true;
    }
    if (l == NULL || r == NULL) {
        return false;
    }
    return isSymmetric(l->l, r->r) && isSymmetric(l->r, r->l);
}

boolean BinaryTree_isSymmetric(BinaryTreeNode * root) {
    if (root == NULL) {
        return true;
    }
    return isSymmetric(root->l, root->r);
}
