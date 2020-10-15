#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1753
최단경로 문제.
다익스트라를 알고 있다면 쉬울 것이요, 아니라면 힘들 것이니....
이 문제를 통해 흐릿했던 나의 다익스트라 지식에 불을 지펴 명확하게 만들었다....
우선 순위 큐를 이용해 적절히 아래 처럼 만들면 된다. 
그냥 밑의 코드가 우선순위 큐를 이용한 다익스트라 그 자체니 머리에 박아둬라...
그리고 정점 배열 엥간하면 맵으로 하지 말고 편하게 벡터로 조져라 괜히 객기 부리지 말고...
*/

#define INF 999999999

typedef struct _www
{
    int To, Weight;
}Point;

bool operator>(Point A, Point B)
{
    return A.Weight > B.Weight;
}

vector<Point> Vertex[20001];
int Dist[20001];
int Vnum, Enum, Start;

void BFS()
{
    priority_queue<Point, vector<Point>, greater<Point>> BFSQ;
    Dist[Start] = 0; BFSQ.push({ Start, 0 });
    while (BFSQ.empty() == false)
    {
        int Weight = BFSQ.top().Weight; int Cur = BFSQ.top().To; BFSQ.pop();
        if (Dist[Cur] < Weight) continue;
        for (int i = 0; i < Vertex[Cur].size(); i++)
        {
            int Next = Vertex[Cur][i].To;
            int NWeight = Vertex[Cur][i].Weight;
            if (Dist[Next] > Weight + NWeight)
            {
                Dist[Next] = Weight + NWeight;
                BFSQ.push({ Next, Dist[Next] });
            }
        }
    }
}

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> Vnum >> Enum >> Start; int From, To, W;
    for (int i = 1; i <= Vnum; i++)
    {
        Dist[i] = INF;
    }
    for (int i = 0; i < Enum; i++)
    {
        cin >> From >> To >> W;
        Vertex[From].push_back({ To, W });
    }
    BFS();
    for (int i = 1; i <= Vnum; i++)
    {
        if (Dist[i] != INF) cout << Dist[i] << '\n';
        else cout << "INF" << '\n';
    }
}