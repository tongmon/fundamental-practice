#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1967
1167번과 같은 트리의 지름 문제이다.
입력 방식만 1167번과 다르기에 자세한 설명은 생략한다.
꼭 트리의 지름 구하는 3가지 단계를 기억하자!
*/

#pragma warning(disable:4996)

typedef struct _edge
{
    short Vertex;
    char Distance;
}Edge;

vector<Edge> Graph[100001];
bool Visited[100001] = { false, };
short Vert = 0; // 정점 개수
Edge Ebuffer;

int DFS(int Starter, int Sum, int* index, vector<int>* Track)
{
    int Bigone = Sum, buffer, P_buffer; Track->push_back(Starter);
    *index = Starter;
    for (int i = 0; i < Graph[Starter].size(); i++)
    {
        if (Visited[Graph[Starter][i].Vertex] == false)
        {
            Visited[Graph[Starter][i].Vertex] = true;
            buffer = DFS(Graph[Starter][i].Vertex, Sum + Graph[Starter][i].Distance, &P_buffer, Track);
            if (buffer > Bigone)
            {
                *index = P_buffer;
                Bigone = buffer;
            }
        }
    }
    return Bigone;
}

int Longest()
{
    vector<int> Track; int Bigone = 0, index;
    Visited[1] = true;
    DFS(1, 0, &index, &Track);
    while (Track.empty() == false)
    {
        Visited[Track.back()] = false;
        Track.pop_back();
    }
    Visited[index] = true;
    return DFS(index, 0, &index, &Track);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> Vert;
    int Num, To, Dist;
    for (int i = 1; i < Vert; i++)
    {
        cin >> Num >> To >> Dist;
        Ebuffer.Distance = Dist; Ebuffer.Vertex = To;
        Graph[Num].push_back(Ebuffer);
        Ebuffer.Vertex = Num;
        Graph[To].push_back(Ebuffer);
    }
    cout << Longest();
}