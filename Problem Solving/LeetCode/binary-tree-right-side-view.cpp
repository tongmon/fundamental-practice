/*
https://leetcode.com/problems/binary-tree-right-side-view/
트리를 오른쪽부터 돌면서 처음 보이는 녀석들부터 추리면 된다.
*/

class Solution
{
    vector<int> r;
public:
    void iter(TreeNode* n, int d)
    { 
        if (!n)
            return;
        if (r.size() <= d)
            r.push_back(n->val);
        iter(n->right, d + 1);
        iter(n->left, d + 1);
    }
    vector<int> rightSideView(TreeNode* root)
    {
        iter(root, 0);
        return r;
    }
};