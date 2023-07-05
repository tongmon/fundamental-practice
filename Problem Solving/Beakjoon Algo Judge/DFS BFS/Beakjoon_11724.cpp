#include <iostream>
#include <cstring>
#include <list>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/11724
기본적인 연결요소 탐색 문제
연결요소를 탐색할 때 자료구조에서 색칠하면서 진행된다는 것을 기억해보면 생각보다 간단하다.
DFS, BFS 모두 가능하나 DFS 구현이 좀 더 간단하기에 DFS로 구현했다.
*/

#pragma warning(disable:4996)

short Graph[1001][1001] = { 0, };
short Dvisited[1001] = { 0, };

void DFS(int Vert, int Starter)
{
    Dvisited[Starter] = 1;
    for (int i = 1; i <= Vert; i++)
    {
        if (Graph[Starter][i] == 1 && Dvisited[i] != 1)
        {
            DFS(Vert, i);
        }
    }
}

int Coloring(int Vert)
{
    int color = 0;
    for (int i = 1; i <= Vert; i++)
    {
        if (Dvisited[i] != 1)
        {
            DFS(Vert, i); color++;
        }
    }
    return color;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int Vert, Edge, row, col;
    cin >> Vert >> Edge;
    for (int i = 0; i < Edge; i++)
    {
        cin >> row >> col;
        Graph[row][col] = 1;
        Graph[col][row] = 1;
    }
    cout << Coloring(Vert);
}