#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/path-sum/
주어진 수가 트리 경로 합으로 나타날 수 있는지 보는 문제.
재귀 기초 문제다.
*/

struct TreeNode 
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) return 0;
        int p = targetSum - root->val;
        if (!p && root->left == root->right) return 1;
        bool r = 0;
        if (root->left)
            r |= hasPathSum(root->left, p);
        if (!r && root->right)
            r |= hasPathSum(root->right, p);
        return r;
    }
};