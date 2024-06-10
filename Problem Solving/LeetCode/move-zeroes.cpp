#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/move-zeroes/
숫자 0을 뒤로 밀면 된다.
*/

class Solution
{
public:
    void moveZeroes(vector<int>& nums)
    {
        for (int i = nums.size() - 1; i >= 0; i--)
        {
            if (!nums[i])
                for (int j = i + 1; j < nums.size(); j++)
                {
                    if (!nums[j])
                        break;
                    nums[j - 1] = nums[j];
                    nums[j] = 0;
                }
        }
    }
};