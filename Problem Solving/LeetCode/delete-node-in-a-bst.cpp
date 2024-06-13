/*
https://leetcode.com/problems/delete-node-in-a-bst/
이진 트리에서의 삭제를 구현하면 된다.
난 왼쪽 자식을 우선순위로 바꿔치는 것으로 정하여 구현했다.
따라서 1. 왼쪽 자식이 있으면 왼쪽 자식을 원래 있던 자리에 올림, 2. 왼쪽 자식이 없으면 오른쪽 자식을 올림, 3. 자식이 없는 녀석은 그냥 지움
위 3가지 조건에 따라 나누어 구현하면 된다.
*/

class Solution
{
    TreeNode* rr = nullptr;
    TreeNode* pp = nullptr;
public:
    void del(TreeNode* r, TreeNode* p, int key)
    {
        if (!r)
            return;

        if (r->val != key)
        {
            del(r->left, r, key);
            del(r->right, r, key);
            return;
        }

        rr = r;
        pp = p;
    }

    TreeNode* deleteNode(TreeNode* root, int key)
    {
        TreeNode* ret = nullptr;

        del(root, nullptr, key);

        if (!rr)
            return root;

        if (rr->left)
        {
            ret = rr->left;
            if (pp)
                (pp->left && pp->left->val == rr->val) ? pp->left = rr->left : pp->right = rr->left;
            TreeNode* t = rr->left;
            while (t->right)
                t = t->right;
            t->right = rr->right;
            delete rr;
            return pp ? root : ret;
        }
        else if (rr->right)
        {
            ret = rr->right;
            if (pp)
                (pp->left && pp->left->val == rr->val) ? pp->left = rr->right : pp->right = rr->right;
            delete rr;
        }
        else
        {
            if (pp)
                (pp->left && pp->left->val == rr->val) ? pp->left = nullptr : pp->right = nullptr;
            delete rr;
        }

        return pp ? root : ret;
    }
};