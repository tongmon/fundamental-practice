#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/container-with-most-water/
투 포인터 문제...
양 끝에서 시작해서 가로 길이는 점점 줄어드니 높이는 무조건 높은 녀석이 우선 순위로 선택되어 포인터가 가리키고 있어야 한다.
*/

class Solution
{
public:
    int maxArea(vector<int>& height)
    {
        int r = 0, st = 0, ed = height.size() - 1;
        while (st < ed)
        {
            r = max(r, min(height[st], height[ed]) * (ed - st));
            height[st] > height[ed] ? ed-- : st++;
        }
        return r;
    }
};