#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1012
DFS로 색칠하는 문제이다.
윗 말 그대로 색칠하듯이 재귀타고 블록 이동해 다니면 풀린다.
*/

short T, Width, Height, Chu, col, row, Dir[4][2] = { {1, 0},{0, 1},{-1, 0},{0, -1} };
short Map[50][50]; bool Visited[50][50];

void MSet(int W, int H)
{
    for (int i = 0; i < H; i++)
    {
        memset(Map[i], 0, sizeof(short) * W); memset(Visited[i], false, sizeof(bool) * W);
    }
}

bool is_Valid(short Col, short Row)
{
    if (0 <= Col && Col < Width && 0 <= Row && Row < Height && Visited[Row][Col] == false && Map[Row][Col] == 1) return true;
    return false;
}

void DFS(short Col, short Row)
{
    Visited[Row][Col] = true;
    for (int i = 0; i < 4; i++)
    {
        if (is_Valid(Col + Dir[i][0], Row + Dir[i][1])) DFS(Col + Dir[i][0], Row + Dir[i][1]);
    }
}

int Color()
{
    int Colored = 0;
    for (int i = 0; i < Height; i++)
    {
        for (int j = 0; j < Width; j++)
        {
            if (Visited[i][j] == false && Map[i][j] == 1) {
                DFS(j, i); Colored++;
            }
        }
    }
    MSet(Width, Height); return Colored;
}

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T; 
    for (int i = 0; i < T; i++)
    {
        cin >> Width >> Height >> Chu;
        for (int j = 0; j < Chu; j++)
        {
            cin >> col >> row; Map[row][col] = 1;
        }
        cout << Color() << '\n';
    }
}