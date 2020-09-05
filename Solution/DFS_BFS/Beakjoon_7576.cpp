#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/7576
BFS 문제이다.
처음엔 DFS로만 생각해서 그런지 오래걸렸다.
탐색 시작점이 여러개이고 동시 다발적으로 계산하는 형태를 취하는 문제는 DFS보다 BFS로 풀릴 가능성이 높다. 이를 명시하도록
그리고 이 문제는 BFS를 알아도 몇 가지 해결할 것이 있는데 날짜를 세는 부분이 문제다.
큐의 원소가 빠질 때마다 날짜를 세버리면 정답보다 많은 날짜가 나오고 이를 해결해주어야한다.
방법이 두가지가 있는데 첫번째 방법부터 말하겠다.
일단 1,2가 BFS큐에 들어갔다고 하면 1과 2가 빠지면서 이웃한 원소들이 큐에 들어오게 될 것이다. 
1, 2가 빠지면 하루가 증가해야하고 나머지 원소들이 들어오면 시작점과 끝점을 계산하여 끝점이 빠지면 하루 증가하고 이런식으로 하루를 증가시켜야한다.
두번째 방식은 큐를 두개 이용하는 방식이다.
한 큐에 있는 것을 빼서 다른 큐에 넣고 다른 큐에 해당하는 녀석에 들어온 원소들을 빼서 다시 원래 큐에 넣고 이렇게 옮겨 담는 식으로 계산하여
옮길때마다 하루 추가하여 푸는 방식이 있다.
나는 두번째 방식으로 해결하였다.
*/

#pragma warning(disable:4996)

typedef struct _cord
{
    int x, y;
}Cordinate;

int M = 0, N = 0, Zero = 0;
int Ary[1001][1001];
short Dir[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };
queue<Cordinate> BFS_Q;
queue<Cordinate> Sub_Q;

bool is_Vailed(int x, int y)
{
    if (x < 0 || y < 0 || x >= N || y >= M)
    {
        return false;
    }
    if (Ary[x][y] != 0)
    {
        return false;
    }
    return true;
}

int BFS()
{
    Cordinate buffer, buffer_2;
    int Days = 0;
    while (Sub_Q.empty() != BFS_Q.empty())
    {
        if (BFS_Q.empty() == false)
        {
            Days++;
        }
        while (BFS_Q.empty() == false)
        {
            buffer = BFS_Q.front(); BFS_Q.pop();
            for (int i = 0; i < 4; i++)
            {
                buffer_2.x = buffer.x + Dir[i][0]; buffer_2.y = buffer.y + Dir[i][1];
                if (is_Vailed(buffer_2.x, buffer_2.y) == true)
                {
                    Sub_Q.push(buffer_2); Ary[buffer_2.x][buffer_2.y] = 1; Zero--;
                }
            }
        }
        if (Sub_Q.empty() == false)
        {
            Days++;
        }
        while (Sub_Q.empty() == false)
        {
            buffer = Sub_Q.front(); Sub_Q.pop();
            for (int i = 0; i < 4; i++)
            {
                buffer_2.x = buffer.x + Dir[i][0]; buffer_2.y = buffer.y + Dir[i][1];
                if (is_Vailed(buffer_2.x, buffer_2.y) == true)
                {
                    BFS_Q.push(buffer_2); Ary[buffer_2.x][buffer_2.y] = 1; Zero--;
                }
            }
        }
    }
    if (Zero > 0)
    {
        return -1;
    }
    return Days - 1;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int Num; bool Comp_Checker = false; 
    Cordinate buffer;
    cin >> M >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> Num;
            Ary[i][j] = Num;
            if (Num == 0)
            {
                Zero++;
                Comp_Checker = true;
            }
            else if (Num == 1)
            {
                buffer.x = i; buffer.y = j;
                BFS_Q.push(buffer);
            }
        }
    }
    if (Comp_Checker == false) // 이미 토마토가 모두 익은 상태
    {
        cout << 0;
    }
    else
    {
        cout << BFS();
    }
}