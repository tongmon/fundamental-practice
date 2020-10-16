#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/15649
백트래킹 문제다...
간단히 재귀호출하여 백트래킹 구현하는 문제라 푸는데 어려움은 없었다.
백트래킹에 대해 감을 잡아가자!
*/

int N, M;
vector<short> Num, Print;

void DFS(int Depth)
{
    if (Depth == M) 
    { 
        for (int i = 0; i < Print.size(); i++)
            cout << Print[i] << ' ';
        cout << '\n'; return;
    }
    for (int i = 0, temp; i < Num.size(); i++)
    {
        temp = Num[i]; Num.erase(Num.begin() + i); Print.push_back(temp);
        DFS(Depth + 1);
        Num.insert(Num.begin() + i, temp); Print.pop_back();
    }
}

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for (int i = 1; i <= N; i++) 
        Num.push_back(i);
    DFS(0);
}