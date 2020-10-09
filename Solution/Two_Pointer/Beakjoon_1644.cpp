#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1644
투 포인터 알고리즘과 에라토스테네스의 체를 알면 쉽게 풀리는 혼합 문제이다.
투 포인터에 대해서는 문제 2003번에서 설명했으니 생략한다.
*/

#pragma warning(disable:4996)

bool Primes[4000001];
int N, Count = 0;
vector<int> Prime;

void Erathos()
{
    for (int i = 3; i <= sqrt(N); i = i + 2)
    {
        for (int j = i * i; j <= N; j = j + i)
        {
            Primes[j] = true;
        }
    }
    Prime.push_back(2);
    for (int i = 3; i <= N; i = i + 2)
    {
        if (Primes[i] == false && i % 2 != 0) Prime.push_back(i);
    }
}

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> N; Erathos();
    int Low = 0, High = 0, Sum = 0;
    while (High < Prime.size() || Sum >= N)
    {
        if (Sum == N) Count++;
        if (Sum >= N)
        {
            Sum = Sum - Prime[Low]; Low++;
        }
        else if (High < Prime.size())
        {
            Sum = Sum + Prime[High]; High++;
        }
    }
    cout << Count;
}