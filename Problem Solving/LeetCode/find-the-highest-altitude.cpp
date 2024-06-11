/*
https://leetcode.com/problems/find-the-highest-altitude/
사이값이 더해진 값들이 주어지는데 원래 각 사잇값이 무엇이였는지 맞추면 된다.
*/

class Solution
{
public:
    int largestAltitude(vector<int>& gain)
    {
        int r = 0, b = r;
        for (int i = 0; i < gain.size(); i++)
        {
            b += gain[i];
            r = max(r, b);
        }
        return r;
    }
};