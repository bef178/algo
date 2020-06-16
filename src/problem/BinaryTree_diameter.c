static int findDiameter(BinaryTreeNode * root, int d) {
    if (root == NULL) {
        return d;
    }
    int depthL = BinaryTree_depth(root->l);
    int depthR = BinaryTree_depth(root->r);
    int diameter = depthL + 2 + depthR;
    d = d > diameter ? d : diameter;
    if (d < depthL * 2) {
        return findDiameter(root->l, d);
    } else if (d < depthR * 2) {
        return findDiameter(root->r, d);
    } else {
        return d;
    }
}

/**
 * return the distance of diameter path ends, -1 for empty tree
 */
int BinaryTree_diameter(BinaryTreeNode * root) {
    return findDiameter(root, -1);
}
