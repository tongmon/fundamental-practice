#include <iostream>
#include <string>
#include <cstring>
#include <list>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2667
이 문제는 약간 나한테 혼동을 줬다.
게임을 자주 만들어보니 좌표계를 쓰는 것이 익숙하여 좌표계를 사용하여서 쉽게 풀었으나...
DFS 문제 같기도 하여 이를 이용하여 풀자하니 약간 이차원배열이 그래프 적으로 쓰이지 않아서 약간 혼동이 왔다.
결국 찾아봤는데 내가 처음에 쓴 방식이 결국에 DFS방식이란다...
생각해보니 깊이 우선 탐색이 맞았다. 4방향으로 한 방향씩 깊이 들어가 탐색하는 방식이기에...
이 문제를 통해 기존의 이차원 배열을 두 정점 사이의 간선의 유무, 아니면 가중치를 표현하는 문제만 있는 것이 아니라
좌표계 처럼 사용하는 경우도 DFS_BFS 방식으로 풀 수 있다는 것을 알았다.
*/

#pragma warning(disable:4996)

int Ary[26][26];
int Vert = 0;

bool is_Vailed(int row, int col)
{
    if (row <= 0 || col <= 0 || row > Vert || col > Vert)
    {
        return false;
    }
    return true;
}

void Search(int row, int col, int *Count)
{
    *Count = *Count + 1;
    Ary[row][col] = 0;
    if (is_Vailed(row + 1, col) == true && Ary[row + 1][col] == 1)
    {
        Search(row + 1, col, Count);
    }
    if (is_Vailed(row - 1, col) == true && Ary[row - 1][col] == 1)
    {
        Search(row - 1, col, Count);
    }
    if (is_Vailed(row, col + 1) == true && Ary[row][col + 1] == 1)
    {
        Search(row, col + 1, Count);
    }
    if (is_Vailed(row, col - 1) == true && Ary[row][col - 1] == 1)
    {
        Search(row, col - 1, Count);
    }
}

void Coloring(vector<int>*Result)
{
    int Count = 0;
    for (int i = 1; i <= Vert; i++)
    {
        for (int j = 1; j <= Vert; j++)
        {
            if (Ary[i][j] != 0)
            {
                Search(i, j, &Count);
            }
            if (Count != 0)
            {
                Result->push_back(Count);
                Count = 0;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    vector<int> Result;
    cin >> Vert;
    for (int i = 1; i <= Vert; i++)
    {
        string buffer; cin >> buffer;
        for (int j = 1; j <= Vert; j++)
        {
            Ary[i][j] = (buffer.at(j - 1) - '0');
        }
    }
    Coloring(&Result);
    cout << Result.size() << "\n";
    sort(Result.begin(), Result.end());
    for (int i = 0; i < Result.size(); i++)
    {
        cout << Result[i] << "\n";
    }
}