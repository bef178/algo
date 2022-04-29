/**
 * Given the root of a binary tree, find the max length of the path between any two nodes.
 *
 * leetcode #543 easy
 * https://leetcode.com/problems/diameter-of-binary-tree/
 */

static
int findDiameterInternal(BinaryTreeNode * root, const int knownDiameter) {
    if (root == NULL) {
        return knownDiameter;
    }
    int depthL = BinaryTree_depth(root->l);
    int depthR = BinaryTree_depth(root->r);
    int diameter = depthL + 2 + depthR;
    int d = knownDiameter > diameter ? knownDiameter : diameter;
    if (d < depthL * 2) {
        return findDiameterInternal(root->l, d);
    } else if (d < depthR * 2) {
        return findDiameterInternal(root->r, d);
    } else {
        return d;
    }
}

public
int findDiameter(BinaryTreeNode * root) {
    return findDiameterInternal(root, 0);
}
