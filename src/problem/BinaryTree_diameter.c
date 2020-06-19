static
int BinaryTree_findDiameter(BinaryTreeNode * root, int d) {
    if (root == NULL) {
        return d;
    }
    int depthL = BinaryTree_depth(root->l);
    int depthR = BinaryTree_depth(root->r);
    int diameter = depthL + 2 + depthR;
    d = d > diameter ? d : diameter;
    if (d < depthL * 2) {
        return BinaryTree_findDiameter(root->l, d);
    } else if (d < depthR * 2) {
        return BinaryTree_findDiameter(root->r, d);
    } else {
        return d;
    }
}

/**
 * leetcode #543 Diameter of Binary Tree
 *
 * return the distance of diameter path ends, 0 for empty tree, 0 for 1-node tree
 */
public
int BinaryTree_diameter(BinaryTreeNode * root) {
    return BinaryTree_findDiameter(root, 0);
}
