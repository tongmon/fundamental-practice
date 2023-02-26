#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2606
그래프 탐색 기초 문제...
그래프 탐색을 빨리 풀 수 있는지 한번 봤다.
*/

bool Visited[101];
vector<int> Computer[101];
int Size, Num;

void BFS()
{
    queue<int> BFSQ;
    Visited[1] = true; BFSQ.push(1); Num = 0; int Front;
    while (BFSQ.empty() == false)
    {
        Front = BFSQ.front();
        for (int i = 0; i < Computer[Front].size(); i++)
        {
            if (Visited[Computer[Front][i]] == false)
            {
                Visited[Computer[Front][i]] = true; BFSQ.push(Computer[Front][i]); Num++;
            }
        }
        BFSQ.pop();
    }
}

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);   
    cin >> Size >> Num; int From, To;
    for (int i = 0; i < Num; i++)
    {
        cin >> From >> To; Computer[From].push_back(To); Computer[To].push_back(From);
    }
    BFS(); cout << Num;
}