/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    /*以t1树储存结果, 不用另开辟一棵树*/
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (!t1 && !t2) {
	    return NULL;
        }
        else if (t1 && !t2) {
            return t1;
        }
        else if (!t1 && t2) {
            return t2;
        }
        else {
            t1->val += t2->val;
            t1->left = mergeTrees(t1->left, t2->left);
            t1->right = mergeTrees(t1->right, t2->right);
            return t1;
        }
    }
};

/*只分两种情况讨论, 当一方为NULL时, 直接返回另一方*/
TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
	if (!t1) { return t2; }
	if (!t2) { return t1; }

	t1->val += t2->val;
	t1->left = mergeTrees(t1->left, t2->left);
	t1->right = mergeTrees(t1->right, t2->right);
	return t1;
}
