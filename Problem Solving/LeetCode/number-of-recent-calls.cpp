/*
https://leetcode.com/problems/number-of-recent-calls/
ping 함수에 들어오는 인자는 무조건 우상향 한다는 조건이 있기 때문에 큐를 사용해 과거에 들어온 녀석 중 불필요한 것들을 빼면 된다.
*/

class RecentCounter
{
    queue<int> q;
public:
    RecentCounter()
    {

    }

    int ping(int t)
    {
        q.push(t);
        while (!q.empty() && q.front() < t - 3000)
            q.pop();
        return q.size();
    }
};