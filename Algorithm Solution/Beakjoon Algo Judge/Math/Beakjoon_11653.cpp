#include <iostream>
#include <cstring>
#include <list>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/11653
소인수분해 문제다.
에라토스테네스의 체를 약간 응용하면 풀 수 있다.
2를 나눌수 있을 때까지 나누면 2의 배수는 모두 날라가고 3도 마찬가지 5도....
*/

#pragma warning(disable:4996)

void PrintPrime(int N)
{
    if (N == 1)
    {
        return;
    }
    if (N == 2)
    {
        cout << N; return;
    }
    for (int i = 2; N != 1; i++)
    {
        if (N % i == 0)
        {
            cout << i << "\n";
            N = N / i; i--;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int N; cin >> N;
    PrintPrime(N);
}