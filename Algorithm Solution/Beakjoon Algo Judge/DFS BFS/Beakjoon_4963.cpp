#include <iostream>
#include <string>
#include <cstring>
#include <list>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/4963
2667번 문제와 비슷하지만 사선이동이 추가된 문제이다.
사선 이동 추가하면 정말 다른게 별거 없다.
*/

#pragma warning(disable:4996)

int Ary[50][50];
int Cord[8][2] = { {0,1}, {1,0}, {1,1}, {-1,0}, {0,-1}, {-1,-1}, {-1,1}, {1,-1} };
int Height = 0, Width = 0;

bool is_Vailed(int row, int col)
{
    if (row < 0 || col < 0 || row >= Height || col >= Width)
    {
        return false;
    }
    return true;
}

void Search(int row, int col)
{
    Ary[row][col] = 0;
    int rowbuffer, colbuffer;
    for (int i = 0; i < 8; i++)
    {
        rowbuffer = row + Cord[i][0]; colbuffer = col + Cord[i][1];
        if (is_Vailed(rowbuffer, colbuffer) == true && Ary[rowbuffer][colbuffer] == 1)
        {
            Search(rowbuffer, colbuffer);
        }
    }
}

int Coloring()
{
    int Color = 0;
    for (int i = 0; i < Height; i++)
    {
        for (int j = 0; j < Width; j++)
        {
            if (Ary[i][j] != 0)
            {
                Search(i, j); Color++;
            }
        }
    }
    return Color;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int Num;
    vector<int> Result;
    while (true)
    {
        cin >> Width >> Height;
        if (Width == 0 && Height == 0)
        {
            break;
        }
        for (int i = 0; i < Height; i++)
        {
            for (int j = 0; j < Width; j++)
            {
                cin >> Num;
                Ary[i][j] = Num;
            }
        }
        Result.push_back(Coloring());
    }
    for (int i = 0; i < Result.size(); i++)
    {
        cout << Result[i] << "\n";
    }
}