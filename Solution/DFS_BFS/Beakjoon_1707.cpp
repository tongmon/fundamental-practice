#include <iostream>
#include <cstring>
#include <list>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1707
이분 그래프인지 반별 문제이다.
약간 연결 성분 문제 심화 버전이라고 볼 수 있다.
처음에 이분 그래프 자체가 먼지 몰라서 찾아봤다. 이분 그래프는 말 그대로 정점을 이분법으로 나눌 수 있는 그래프이다.
인접하면 다른 색, 인접하지 않다면 같은 색으로 칠해주면서 나아가면 찾을 수 있다.
만약에 인접했는데 같은 색이 존재하면 이분 그래프가 아닌 것이다.
위와 같은 원리를 이해했고 배열 초기화만 잘해주면 통과하기 수월한 문제이다.
*/

#pragma warning(disable:4996)

vector<int> Graph[20001];

bool DFS(char* visited, int Starter, char Color = 1)
{
    visited[Starter] = Color; bool result = true;
    for (int i = 0; i < Graph[Starter].size(); i++)
    {
        int index = Graph[Starter].at(i);
        if (visited[index] == 0) // 인접한 정점은 다른 색으로
        {
            if (Color == 1)
            {
                result = DFS(visited, index, 2);
            }
            else
            {
                result = DFS(visited, index, 1);
            }
        }
        else if (visited[index] == Color) // 이분 그래프 탈락
        {
            result = false;
        }
        if (result == false)
        {
            return false;
        }
    }
    return result;
}

bool Coloring(int Vert)
{
    char* visited = new char[Vert + 1]; bool result = true;
    memset(visited, 0, sizeof(char) * (Vert + 1));
    for (int i = 1; i <= Vert; i++)
    {
        if (visited[i] == 0)
        {
            result = DFS(visited, i);
            if (result == false)
            {
                return result;
            }
        }
    }
    delete[]visited;
    return result;
}

void Clearing(int Vert)
{
    for (int i = 1; i <= Vert; i++)
    {
        Graph[i].clear();
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int T, Vert, Edge, raw, col;
    vector<bool> Result;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        cin >> Vert >> Edge;
        for (int j = 0; j < Edge; j++)
        {
            cin >> raw >> col;
            Graph[raw].push_back(col);
            Graph[col].push_back(raw);
        }
        Result.push_back(Coloring(Vert));
        Clearing(Vert);
    }
    for (int i = 0; i < Result.size(); i++)
    {
        if (Result[i] == true)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }
}