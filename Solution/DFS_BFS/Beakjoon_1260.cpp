#include <iostream>
#include <cstring>
#include <list>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1260
기본적인 DFS, BFS 개념 이해 문제...
DFS, BFS 문제 풀기 전에 필수로 풀고 넘어가자.
기본적으로 visited는 들어간다.
*/

#pragma warning(disable:4996)

short Graph[1001][1001] = { 0, };
short Dvisited[1001] = { 0, };
short Bvisited[1001] = { 0, };

void BFS(int Vert, int Starter)
{
    short buffer;
    queue<short> Storage;
    for (int i = 1; i <= Vert; i++)
    {
        if (Graph[Starter][i] == 1)
        {
            Storage.push(i); Bvisited[i] = 1;
        }
    }
    Bvisited[Starter] = 1; cout << Starter << " ";
    while (Storage.empty() == false)
    {
        buffer = Storage.front(); Storage.pop();
        cout << buffer << " ";
        for (int i = 1; i <= Vert; i++)
        {
            if (Graph[buffer][i] == 1 && Bvisited[i] != 1) // 연결되어있고 방문하지 않았다면
            {
                Storage.push(i); Bvisited[i] = 1;
            }
        }
    }
    cout << "\n";
}

void DFS(int Vert, int Starter)
{
    cout << Starter << " "; Dvisited[Starter] = 1;
    for (int i = 1; i <= Vert; i++)
    {
        if (Graph[Starter][i] == 1 && Dvisited[i] != 1)
        {
            DFS(Vert, i);
        }
    }
}


int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int Vert, Edge, start, row, col;
    cin >> Vert >> Edge >> start;
    for (int i = 0; i < Edge; i++)
    {
        cin >> row >> col;
        Graph[row][col] = 1;
        Graph[col][row] = 1;
    }
    DFS(Vert, start); cout << "\n";
    BFS(Vert, start);
}