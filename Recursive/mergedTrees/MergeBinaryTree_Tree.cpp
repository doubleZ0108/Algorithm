/*
接口程序 & 测试程序: https://leetcode-cn.com/problems/merge-two-binary-trees/
*/

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


/*完全重新开辟一棵新树*/
TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
	TreeNode *root;
	TreeNode *left1 = NULL, *left2 = NULL, *right1 = NULL, *right2 = NULL;

	if (!t1 && !t2) { return NULL; }
	else if (t1 && t2)
	{
		root = new TreeNode(t1->val + t2->val);
		left1 = t1->left;
		left2 = t2->left;
		right1 = t1->right;
		right2 = t2->right;
	}
	else if (t1 && !t2)
	{
		root = new TreeNode(t1->val);
		left1 = t1->left;
		right1 = t1->right;
	}
	else
	{
		root = new TreeNode(t2->val);
		left2 = t2->left;
		right2 = t2->right;
	}

	root->left = mergeTrees(left1, left2);
	root->right = mergeTrees(right1, right2);

	return root;
}
