static int findDiameter(BinaryTreeNode * root, int d) {
    if (root == NULL) {
        return d >= 0 ? d : 0;
    }
    int depthL = BinaryTree_depth(root->l);
    int depthR = BinaryTree_depth(root->r);
    d = d >= (depthL + 1 + depthR) ? d : (depthL + 1 + depthR);
    if (d < depthL * 2 - 1) {
        return findDiameter(root->l, d);
    } else if (d < depthR * 2 - 1) {
        return findDiameter(root->r, d);
    } else {
        return d;
    }
}

/**
 * return the number of nodes that in diameter path, 0 for NULL-tree
 */
int BinaryTree_diameter(BinaryTreeNode * root) {
    return findDiameter(root, 0);
}
