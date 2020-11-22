#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1987
DFS로 풀어야 간단해지는 탐색 문제다.
여느 격자 탐색문제와 같이 상하좌우로 뻗어나가며 탐색이 진행되는데 이 때 길이의 최대 경우를 구하는 문제기에
BFS로 접근하면 까다로워진다.
DFS로 접근하되 알파벳 만큼을 Visited 배열로 선언하고 계속 깊이 들어가다가 끝에 도착하면 다시 뒤로 빠지면서 자신이
갔던 흔적을 지워야 다른 가능성 경로들도 탐색이 가능해진다. 약간 순열 알고리즘에서 재귀 돌릴 때 스왑 쌍으로 붙이는 것과
비슷한 원리이다.
이 문제를 풀면서 탐색 문제에서 최대 경로를 찾는 문제를 어떻게 접근하는지 약간의 감을 더 키웠다.
*/

#pragma warning(disable:4996)

int Width, Height, MAX = 0, Dir[4][2] = { {-1, 0},{1, 0},{0, -1},{0, 1} };
bool Visited[27];
char Ary[30][30];

bool is_Vailed(int Col, int Row)
{
    if (0 <= Col && Col < Height && 0 <= Row && Row < Width) return true;
    return false;
}

void DFS(int Col, int Row, int Depth)
{
    Visited[Ary[Col][Row] - 'A'] = true;
    bool goDown = false;
    for (int i = 0; i < 4; i++)
    {
        if (is_Vailed(Col + Dir[i][0], Row + Dir[i][1]) == true && Visited[Ary[Col + Dir[i][0]][Row + Dir[i][1]] - 'A'] == false)
        {
            goDown = true;
            DFS(Col + Dir[i][0], Row + Dir[i][1], Depth + 1);
            Visited[Ary[Col + Dir[i][0]][Row + Dir[i][1]] - 'A'] = false;
        }
    }
    if (goDown == false && MAX < Depth) MAX = Depth;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> Height >> Width;
    for (int i = 0; i < Height; i++)
    {
        for (int j = 0; j < Width; j++)
        {
            cin >> Ary[i][j];
        }
    }
    DFS(0, 0, 1);
    cout << MAX;
}