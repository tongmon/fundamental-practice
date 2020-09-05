#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2178
7576번 문제와 유사한 BFS 문제이다.
BFS에서 탐색 중 가장 먼저 도착한 루트가 가장 빠르다라는 사실을 이용하면 쉽게 풀린다...
사실 7576번 문제를 풀었다면 코드 몇줄 바꾸면 끝난다...
이 문제는 시작점이 여러개는 아니지만 최단 경로를 찾는 것이기에 BFS를 고려해봐야 한다.
*/

#pragma warning(disable:4996)

typedef struct _cord
{
    int x, y;
}Cordinate;

int Width = 0, Height = 0;
int Ary[101][101];
short Dir[4][2] = { {0,1},{-1,0},{0,-1},{1,0} };
queue<Cordinate> BFS_Q;
queue<Cordinate> Sub_Q;

bool is_Vailed(Cordinate *A)
{
    if (A->x < 0 || A->y < 0 || A->x >= Height || A->y >=Width)
    {
        return false;
    }
    if (Ary[A->x][A->y] != 1)
    {
        return false;
    }
    return true;
}

int BFS()
{
    int Shortest = 0;
    Cordinate buffer, buffer_2; 
    buffer.x = 0, buffer.y = 0;
    BFS_Q.push(buffer);
    while (BFS_Q.empty() != Sub_Q.empty())
    {
        if (BFS_Q.empty() == false)
        {
            Shortest++;
        }
        while (BFS_Q.empty() == false)
        {
            buffer = BFS_Q.front(); BFS_Q.pop();
            for (int i = 0; i < 4; i++)
            {
                buffer_2.x = buffer.x + Dir[i][0]; buffer_2.y = buffer.y + Dir[i][1];
                if (is_Vailed(&buffer_2) == true)
                {
                    if (buffer_2.x == Height - 1 && buffer_2.y == Width - 1)
                    {
                        return Shortest + 1;
                    }
                    Ary[buffer_2.x][buffer_2.y] = 0; 
                    Sub_Q.push(buffer_2);
                }
            }
        }
        if (Sub_Q.empty() == false)
        {
            Shortest++;
        }
        while (Sub_Q.empty() == false)
        {
            buffer = Sub_Q.front(); Sub_Q.pop();
            for (int i = 0; i < 4; i++)
            {
                buffer_2.x = buffer.x + Dir[i][0]; buffer_2.y = buffer.y + Dir[i][1];
                if (is_Vailed(&buffer_2) == true)
                {
                    if (buffer_2.x == Height - 1 && buffer_2.y == Width - 1)
                    {
                        return Shortest + 1;
                    }
                    Ary[buffer_2.x][buffer_2.y] = 0;
                    BFS_Q.push(buffer_2);
                }
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int Num = 0; string buffer;
    cin >> Height >> Width;
    for (int i = 0; i < Height; i++)
    {
        cin >> buffer;
        for (int j = 0; j < Width; j++)
        {
            Ary[i][j] = (buffer.at(j) - '0');
        }
    }
    cout << BFS();
}