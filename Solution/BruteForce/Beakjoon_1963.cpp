#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1963
BFS + 완전 탐색 + 에라토스테네스의 체 짬뽕 문제다.
일단 이 문제는 처음에 1033 1733 3733 3739 3779 8779 8179 이렇게 진행이 된다고 해서
무슨 규칙이지? 한번은 게다가 결과값 8179 보다 높은 8779를 거쳐가네? 하며 쓸데없이 억지로 규칙을 찾아내려 하였다.
그래서 규칙을 발견하지 못하겠어서 완전탐색을 돌리려해보니 이때 접근 방법을 알아내는 것도 좀 곤란했다....
알고리즘 분류를 보니 BFS가 있더라.... 그 순간 풀이법을 깨달았다... 사실상 힌트를 봐버린거지 뭐
일단 완전 탐색 문제를 몇개 풀어보니 완전 탐색은 태생이 탐색이기 때문에 DFS_BFS와 굉장히 밀접하다. 
일단 규칙이 없다 -> 완전 탐색을 시도해본다 -> 그냥 포문돌려서 접근하기 어렵다 -> BFS_DFS를 시도해본다....
완전 탐색 문제를 풀 때 이러한 사고방식이 필요한 것 같다. 
일단 BFS를 떠올리지도 못했으니까 이러한 사고방식을 머릿속에 박아두자!
*/

#pragma warning(disable:4996)

#define SIZE 10000
bool Primes[SIZE]; // false는 소수
int Visited[SIZE];

void Erathos()
{
    for (int i = 4; i < SIZE; i = i + 2)
    {
        Primes[i] = true;
    }
    for (int i = 3; i <= sqrt(SIZE - 1); i = i + 2)
    {
        for (int j = i * i; j < SIZE; j = j + i)
        {
            Primes[j] = true;
        }
    }
}

void Push(queue<int> *BFSQ, int Sub)
{
    int Num = (BFSQ->front() / (int)pow(10, Sub)) % 10, Counter = 0;
    int Starter = BFSQ->front() - (int)pow(10, Sub) * Num;
    if (Sub == 3)
    {
        Counter = 1;
        Starter = BFSQ->front() - (int)pow(10, Sub) * (Num - 1);
    }
    while (Counter < 10)
    {
        if (Visited[Starter] == 0 && Primes[Starter] == false)
        {
            BFSQ->push(Starter); Visited[Starter] = Visited[BFSQ->front()] + 1;
        }
        Starter = Starter + (int)pow(10, Sub);
        Counter++;
    }
}

int ConvertNum(int start, int end)
{
    if (start == end) return 0;
    queue<int> BFSQ;
    BFSQ.push(start); Visited[start] = 1;
    while (BFSQ.empty() == false)
    {
        if (BFSQ.front() == end)
        {
            return Visited[BFSQ.front()] - 1;
        }
        for (int i = 0; i < 4; i++)
        {
            Push(&BFSQ, i);
        }
        BFSQ.pop();
    }
    return -1;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    Erathos(); int T, start, end;
    vector<int> Result;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        cin >> start >> end;
        Result.push_back(ConvertNum(start, end));
        memset(Visited, 0, SIZE * sizeof(int));
    }
    for (int i = 0; i < T; i++)
    {
        if (Result[i] == -1)
        {
            cout << "Impossible" << '\n';
        }
        else
        {
            cout << Result[i] << '\n';
        }
    }
}