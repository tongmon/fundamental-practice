#include <iostream>
#include <cstring>
#include <list>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2331
그래프 문제라고 해서 "뭐지? 전혀 그렇게 안보이는데" 라고 생각하고
그냥 단순하게 싸이클 찾는 이중for문 돌려서 풀었는데 시간초과 안나고 풀려서 놀랐다....
다른 사람 풀이를 보니 BFS_DFS로 풀었던데 왜 내가 이 생각을 못했는지....
2가지 방법을 모두 제시해 둔다.
DFS로 풀경우 시작수 A가 루프 안에 들어갈 경우 0을 출력해주는 반례가 있으니 유의하자.
이 문제에서 중요하게 봐야할 것은 특정 규칙을 가지는 배열의 싸이클을 검사할 때 DFS_BFS의 방법이 쓰일 수가 있다는 것이다.
*/

#pragma warning(disable:4996)

int Visited[3000001] = { 0, }; // 9999이고 P가 5일 경우 제일 커지는 값이 3000000을 넘지 않는다.
int Count = 0;

bool DFS(int Starter, int P, int A)
{
    if (Visited[Starter] == 0)
    {
        Visited[Starter] = ++Count;
        int Sum = 0;
        while (Starter > 0)
        {
            Sum = Sum + pow(Starter % 10, P); Starter = Starter / 10;
        }
        if (DFS(Sum, P, A) == false)
        {
            return false;
        }
    }
    else
    {
        if (A == Starter)
        {
            cout << 0;
        }
        else
        {
            cout << Visited[Starter] - 1;
        }
        return false;
    }
}

int main() // DFS로 해결
{
    ios::sync_with_stdio(false); cin.tie(0);
    int A, P;
    cin >> A >> P;
    DFS(A, P, A);
}

/*
int Ary[20000];

int main() // 단순한 싸이클 검사로 해결
{
    ios::sync_with_stdio(false); cin.tie(0);
    int A, P, buffer, Sum, j;
    cin >> A >> P;
    Ary[0] = A;
    for (int i = 1;;i++)
    {
        buffer = Ary[i - 1]; Sum = 0;
        while (buffer > 0)
        {
            Sum = Sum + pow(buffer % 10, P); buffer = buffer / 10;
        }
        for (j = i - 1; j >= 0; j--)
        {
            if (Sum == Ary[j])
            {
                cout << j; break;
            }
        }
        if (Sum == Ary[j])
        {
            break;
        }
        Ary[i] = Sum;
    }
}
*/