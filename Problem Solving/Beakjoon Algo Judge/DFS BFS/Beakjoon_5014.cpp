#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/5014
탐색으로 최단거리 찾는 문제이다.
일단 탐색에서 DFS, BFS를 떠올릴 수 있어야하고 최단거리를 찾는 다는 점에서 BFS가 우선이 되어야 한다.
믈론 DFS로 찾을 수도 있지만 번거롭고 예외처리해야 할 상황이 많아진다.
내가 처음에 이 문제를 DFS로 접근해서 풀려하였고 위층, 아래층으로 이동하는 층수가 0인 경우인 예외 상황도 문제가 되고
결국에 DFS로 풀었다고 해도 시간초과로 문제를 틀렸다.
그 후 BFS로 접근을 해서 문제를 풀게 되었다.
다시 꼭 기억하자. 최단 거리를 구해야하는 탐색 문제는 DFS가 아닌 BFS로 접근해야 한다는 것을...
그리고 가장 기초적인 부분에서 많은 실수를 했는데 1~1000 범위를 visite 체크하는 배열은 visite[1000]이 아닌 visite[1001]이다!
앞으로 멍청한 실수하지 마라 
너는 DP 문제 풀 때 뼈저리게 느꼈으면서 또 같은 실수를 하냐...
*/

#pragma warning(disable:4996)

int F, S, G, U, D;
int Visited[1000001];

/*
// DFS 방식으로 풀어보려 했지만 시간초과가 난다.
void DFS(int Cur, int botton)
{
    if (Cur < 1 || Cur > F || Visited[Cur] != -1) return;
    Visited[Cur] = botton;
    if (Cur == G)
    {
        if (botton < Minimum) Minimum = botton;
        return;
    }
    if (Cur + U != Cur) {
        DFS(Cur + U, botton + 1);
        if (Cur + U >= 1 && Cur + U <= F) Visited[Cur + U] = -1;
    }
    if (Cur - D != Cur) {
        DFS(Cur - D, botton + 1);
        if (Cur - D >= 1 && Cur - D <= F) Visited[Cur - D] = -1;
    }
}
*/

int BFS(int Cur)
{
    queue<int> BFSQ;
    BFSQ.push(Cur); Visited[Cur] = 0;
    while (BFSQ.empty() == false)
    {
        if (BFSQ.front() == G) return Visited[G];
        if (BFSQ.front() + U >= 1 && BFSQ.front() + U <= F && Visited[BFSQ.front() + U] == -1)
        {
            BFSQ.push(BFSQ.front() + U); Visited[BFSQ.front() + U] = Visited[BFSQ.front()] + 1;
        }
        if (BFSQ.front() - D >= 1 && BFSQ.front() - D <= F && Visited[BFSQ.front() - D] == -1)
        {
            BFSQ.push(BFSQ.front() - D); Visited[BFSQ.front() - D] = Visited[BFSQ.front()] + 1;
        }
        BFSQ.pop();
    }
    return -1;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    memset(Visited, -1, sizeof(Visited));
    cin >> F >> S >> G >> U >> D;
    int ans = BFS(S);
    if (ans == -1) cout << "use the stairs";
    else cout << ans;
}