#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1697
BFS로 완전탐색하는 문제이다...
풀면서 빡친게 왜 BFS는 생각했으면서 Visited배열 선언을 안해서 개뻘짓을 했는지 모르겠다....
그냥 Visited 배열만 선언해서 해결하면 되는 것을 왜 도대체 안 써가지고 메모리 초과를 몇번이나 내고.....
똑바로 기억하자 BFS, DFS는 Visited를 사용한다는 것을...
문제를 풀면서 깨달은 점은 이러한 완전탐색 문제는 잔실수를 줄이는 것이 실력이라는 것이다.
잔 실수를 지금의 내 실력으로는 빠르게 줄이기가 힘든게 사실이다. 빠르게 실력을 키워 잔실수를 없애자!
그리고 밑의 소스는 그냥 큐가 비어있을 때 까지 다 돌아도 되지만 속도를 더 빠르게 하기위해 시간으로 중단점을 잡았다.
*/

#pragma warning(disable:4996)

int Subin, Sister;
int Min = 2000000000;
bool Visited[1000002];

typedef struct _TAC
{
    int Time, Loc;
}TAC;

void Push(int Cur, int time, queue<TAC>* Time_set)
{
    TAC buffer; buffer.Time = time;
    if (0 != Cur && Visited[Cur - 1] == false)
    {
        buffer.Loc = Cur - 1;
        Visited[Cur - 1] = true;
        Time_set->push(buffer);
    }
    if (100000 != Cur && Visited[Cur + 1] == false)
    {
        buffer.Loc = Cur + 1;
        Visited[Cur + 1] = true;
        Time_set->push(buffer);
    }
    if (Cur <= 50000 && 0 < Cur && Visited[Cur * 2] == false)
    {
        buffer.Loc = Cur * 2;
        Visited[Cur * 2] = true;
        Time_set->push(buffer);
    }
}

void BFS(int Cur, int Dest)
{
    if (Cur >= Dest)
    {
        Min = Cur - Dest; return;
    }
    queue<TAC> Time_set; int Time = 1;
    Push(Cur, Time, &Time_set);
    while (true)
    {
        Cur = Time_set.front().Loc; Time = Time_set.front().Time; Time_set.pop();
        if (Min <= Time)
        {
            return;
        }
        if (Dest == Cur)
        {
            if (Min > Time)
            {
                Min = Time;
            }
            return;
        }
        else if (Dest < Cur)
        {
            if (Min > Time + Cur - Dest)
            {
                Min = Time + Cur - Dest;
            }
        }
        else
        {
            Push(Cur, Time + 1, &Time_set);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> Subin >> Sister;
    BFS(Subin, Sister);
    cout << Min;
}