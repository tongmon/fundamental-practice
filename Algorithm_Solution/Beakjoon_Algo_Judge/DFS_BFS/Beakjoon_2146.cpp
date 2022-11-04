#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2146
이 문제... 푸는데 존나 오래걸렸다.... 아니 아이디어는 짰는데 구현하는데 오래걸렸다고 해야하나...
일단 내가 쓴 방법은 섬들이 주어지면 DFS로 각 섬마다 해당하는 번호를 매겨 맵 배열에 새긴다. (BFS도 상관없다.)
이때 번호를 새길때 나중에 순회할 BFS 큐에 넣어둔다. 고유한 BFS큐의 개수는 따라서 섬의 개수와 같다.
이렇게 번호를 다 새기고 섬마다 큐를 다 만들었으면 최단 거리를 구해야하는데 이 최단거리를 구할때
BFS를 사용하여 구한다. 큐에 해당하는 섬에서 가장 먼저 다른 섬에 도착하는 경로가 빠른 것이다.
이렇게 큐마다 가장 빠른 경로를 구하고 비교해서 가장 적은 경로를 찾아 출력하는 방식이다.
다른 사람들 풀이를 보니 나와 로직은 비슷하지만 visited배열을 사용했다.
나도 사용하려 했지만 memset 속도 때문에 사용하지 않고 그냥 풋스텝이라는 발자국을 남기는 방식을 사용했다.
이 문제를 통해서 DFS, BFS를 혼용해서 사용하는 문제에 대한 깨달음을 약간 얻을 수 있었다.
*/

#pragma warning(disable:4996)

typedef struct _cord
{
    char x = 0, y = 0;
}Cordinate;

int Ary[101][101], N = 0;
short Dir[4][2] = { { 0,1 }, { -1,0 }, { 1,0 }, { 0,-1 } };
vector<queue<Cordinate>> Islands;

bool is_Vailed(Cordinate *A)
{
    if (A->x < 0 || A->y < 0 || A->x >= N || A->y >= N)
    {
        return false;
    }
    return true;
}

void DFS(int x, int y, int Color)
{
    Ary[x][y] = Color;
    Cordinate buffer, buffer_2; 
    buffer.x = x; buffer.y = y;
    Islands[Color - 2].push(buffer);
    for (int i = 0; i < 4; i++)
    {
        buffer_2.x = buffer.x + Dir[i][0];
        buffer_2.y = buffer.y + Dir[i][1];
        if (is_Vailed(&buffer_2) == true && Ary[buffer_2.x][buffer_2.y] == 1)
        {
            DFS(buffer_2.x, buffer_2.y, Color);
        }
    }
}

void Coloring()
{
    int Color = 2; queue<Cordinate> Q_buffer;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (Ary[i][j] == 1)
            {
                Islands.push_back(Q_buffer);
                DFS(i, j, Color); Color++;
            }
        }
    }
}

int BFS(int index, int FootPrint)
{
    Cordinate buffer, buffer_2;
    int Shortest = 0;
    queue<Cordinate> Sub_Q;
    while (Islands[index].empty() != Sub_Q.empty())
    {
        Shortest++;
        while (Islands[index].empty() == false)
        {
            buffer = Islands[index].front(); Islands[index].pop();
            for (int i = 0; i < 4; i++)
            {
                buffer_2.x = buffer.x + Dir[i][0]; buffer_2.y = buffer.y + Dir[i][1];
                if (is_Vailed(&buffer_2) == true && Ary[buffer_2.x][buffer_2.y] != index + 2)
                {
                    if (Ary[buffer_2.x][buffer_2.y] >= FootPrint || Ary[buffer_2.x][buffer_2.y] == 0)
                    {
                        if (Ary[buffer_2.x][buffer_2.y] != FootPrint + index)
                        {
                            Sub_Q.push(buffer_2);
                            Ary[buffer_2.x][buffer_2.y] = FootPrint + index;
                        }
                    }
                    else if (Ary[buffer_2.x][buffer_2.y] < FootPrint && Ary[buffer_2.x][buffer_2.y] > 0)
                    {
                        return Shortest - 1;
                    }
                }              
            }
        }
        Shortest++;
        while (Sub_Q.empty() == false)
        {
            buffer = Sub_Q.front(); Sub_Q.pop();
            for (int i = 0; i < 4; i++)
            {
                buffer_2.x = buffer.x + Dir[i][0]; buffer_2.y = buffer.y + Dir[i][1];
                if (is_Vailed(&buffer_2) == true && Ary[buffer_2.x][buffer_2.y] != index + 2)
                {
                    if (Ary[buffer_2.x][buffer_2.y] >= FootPrint || Ary[buffer_2.x][buffer_2.y] == 0)
                    {
                        if (Ary[buffer_2.x][buffer_2.y] != FootPrint + index)
                        {
                            Islands[index].push(buffer_2);
                            Ary[buffer_2.x][buffer_2.y] = FootPrint + index;
                        }
                    }
                    else if (Ary[buffer_2.x][buffer_2.y] < FootPrint && Ary[buffer_2.x][buffer_2.y] > 0)
                    {
                        return Shortest - 1;
                    }
                }
            }
        }
    }
    return Shortest;
}

int Shortest()
{
    int Shortest = 999, Comp, FootPrint = Islands.size() + 2; // color가 인덱스 +2이기 때문
    for (int i = 0; i < Islands.size() - 1; i++)
    {
        Comp = BFS(i, FootPrint);
        if (Comp < Shortest)
        {
            Shortest = Comp;
        }
    }
    return Shortest;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int Num;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> Num;
            Ary[i][j] = Num;
        }
    }
    Coloring();
    cout << Shortest();
}