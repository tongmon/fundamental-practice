/*
https://leetcode.com/problems/keys-and-rooms/
DFS 문제...
*/

class Solution
{
    vector<vector<int>>* r;
    vector<bool> v;
public:
    void vis(int o, vector<int>& k)
    {
        v[o] = true;
        for (const auto& e : k)
            if (!v[e])
                vis(e, r->at(e));
    }

    bool canVisitAllRooms(vector<vector<int>>& rooms)
    {
        r = &rooms;
        v.resize(r->size());
        v[0] = true;

        vis(0, r->at(0));

        bool ret = true;
        for (int i = 0; i < v.size() && ret; i++)
            ret &= v[i];
        return ret;
    }
};