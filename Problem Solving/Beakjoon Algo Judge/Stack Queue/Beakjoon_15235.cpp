/*
https://www.acmicpc.net/problem/15235
큐를 이용하여 뺑뺑이 돌리면 된다.
큐 최대 크기가 1000, 각 원소 숫자의 최대 크기가 1000이라 1000 * 1000은 1억 미만이기에 1초 이내에 풀 수 있다.
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    queue<pair<int, int>> q;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> m;
        q.push({i, m});
    }
    n = 0;
    while (!q.empty())
    {
        n++;
        auto f = q.front();
        q.pop();
        if (--f.second)
            q.push(f);
        else
            a[f.first] = n;
    }
    for (const auto &t : a)
        cout << t << ' ';
}