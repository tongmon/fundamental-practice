#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1167
트리의 지름 구하는 문제... 개뻘짓하다가 못풀고 해답을 봤더니 역시 무친 사람들이 많다.
뻘짓을 더했으면 큰일 났을 뻔한 문제... 모르면 풀기 존나 힘든 문제였다.
처음에 다익스트라로 풀까도 생각했지만 시간복잡도에서 답이 없어서 시도도 안했다.
암튼 각설하고 트리의 지름을 구하는 방법은 다음과 같다.
1) 아무 정점 v를 잡고 v와 가장 멀리 떨어져있는 정점 w를 찾자.
2) 찾은 w에서 가장 멀리 떨어져있는 정점 p를 찾자
3) w와 p 사이의 거리가 트리의 지름이 된다.
처음엔 ???!!! 할 수 있다. 증명은 https://www.weeklyps.com/entry/%ED%8A%B8%EB%A6%AC%EC%9D%98-%EC%A7%80%EB%A6%84 이곳이 잘 설명되어 있으니
한번 봐보자.
결국엔 위 3가지 순서를 구현한다하면 DFS를 2번 행하면 끝나는 문제가 된다.
*/

#pragma warning(disable:4996)

typedef struct _edge
{
    int Vertex;
    short Distance;
}Edge;

vector<Edge> Graph[100001];
bool Visited[100001] = { false, };
int Vert = 0; // 정점 개수
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
    int Num, Vertex, Dist;
    for (int i = 0; i < Vert; i++)
    {
        cin >> Vertex;
        while (true)
        {
            cin >> Num;
            if (Num == -1)
            {
                break;
            }
            cin >> Dist;
            Ebuffer.Vertex = Num; Ebuffer.Distance = Dist;
            Graph[Vertex].push_back(Ebuffer);
        }
    }
    cout << Longest();
}