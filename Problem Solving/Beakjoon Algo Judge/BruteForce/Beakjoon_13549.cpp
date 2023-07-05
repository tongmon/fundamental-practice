#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/13549
저번 1697번 풀었던 소스에서 조금만 비틀면 풀리는 문제다.
같은 BFS로 풀 수 있지만 차이라 하면 우선순위가 생긴다는 것이다.
2배로 뛰어 이동시에는 0초가 걸리기에 최소로 걸리는 경우를 구하기 위해선 2배로 뛰는 경우의 우선순위를
제일 높게 쳐야한다. 그렇게해서 쿠 삽입시에 제일 먼서 Visited[]에 방문 표시를 할 수 있게 해주는 방식으로 풀었다.
문제를 풀면서 깨달은 점은 우선순위가 생기는 경우에도 BFS로 문제를 풀 수가 있고 이를 적용하는 방식은
큐에 원소를 삽입 시에 먼저 삽입한다는 것이다. 이 점을 알아가자.
다른 사람 풀이를 보니 이 문제는 정말 다양한 풀이가 많았다.
우선순위 큐를 활용하여 푸는 풀이가 있었다. 시간이 적은 녀석이 계속 위에 올라오게 되니 맨 위의 녀석의 좌표가 동생 위치와 같으면 그게 답인 방법이다.
아니면 이분법적인 우선순위를 활용해 순간이동시에는 덱의 앞쪽에 그냥 한칸이동시에는 덱의 뒤쪽에 넣고 앞쪽을 팝하면서 계속 검사하는 이러한 방식도 있었다.
이런 방식을 기억해놨다가 나중에 써먹자!
*/

#pragma warning(disable:4996)

int Subin, Sister;
int Min = 2000000000;
bool Visited[1000002];

typedef struct _TAC
{
    int Time, Loc;
}TAC;

void Push(int Cur, int time, queue<TAC> *Time_set)
{
    TAC buffer; buffer.Time = time - 1;
    if (Cur <= 50000 && 0 < Cur && Visited[Cur * 2] == false)
    {
        buffer.Loc = Cur * 2;
        Visited[Cur * 2] = true;
        Time_set->push(buffer);
    }
    buffer.Time = time;
    if (0 < Cur && Visited[Cur - 1] == false)
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
}

void BFS(int Cur, int Dest)
{
    if (Cur >= Dest)
    {
        Min = Cur - Dest; return;
    }
    queue<TAC> Time_set; int Time = 1;
    Push(Cur, Time, &Time_set);
    while (Time_set.empty() == false)
    {
        Cur = Time_set.front().Loc; Time = Time_set.front().Time; Time_set.pop();
        if (Dest <= Cur)
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