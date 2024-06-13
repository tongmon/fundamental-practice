/*
https://leetcode.com/problems/nearest-exit-from-entrance-in-maze/
최단 거리 문제이기에 BFS를 이용한다.
BFS의 기본은 큐 사용이다.
*/

class Solution
{
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance)
    {
        int r = INT_MAX;
        pair<int, int> w[4] = { {1,0},{0,1},{-1,0},{0,-1} };       
        vector<vector<int>> v(maze.size());
        for (auto& vv : v)
            vv.resize(maze[0].size(), 0);
        queue<pair<int, int>> q;
        q.push({ entrance[0], entrance[1] });
        v[entrance[0]][entrance[1]] = 1;
        while (!q.empty())
        {
            auto c = q.front();
            if ((!c.first || !c.second || c.first == maze.size() - 1 || c.second == maze[0].size() - 1) && (entrance[0] != c.first || entrance[1] != c.second))
                r = min(r, v[c.first][c.second]);
            q.pop();
            for (int i = 0; i < 4; i++)
            {
                int th = c.first + w[i].first, tw = c.second + w[i].second;
                if (0 <= th && th < maze.size() && 0 <= tw && tw < maze[0].size() && !v[th][tw] && maze[th][tw] == '.')
                {
                    q.push({ th,tw });
                    v[th][tw] = v[c.first][c.second] + 1;
                }
            }
        }
        return r == INT_MAX ? -1 : r - 1;
    }
};