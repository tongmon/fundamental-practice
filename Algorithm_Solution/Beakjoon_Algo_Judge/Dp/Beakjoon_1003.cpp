#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1003
기본적인 Dp문제다. 피보나치의 점화식을 생각해보면 간단히 풀수있다.
*/

#pragma warning(disable:4996)

int Dp_zero[41] = {1,0,1,};
int Dp_one[41] = {0,1,1,};

void Fib(int N)
{
    for (int i = 3; i <= N; i++)
    {
        Dp_zero[i] = Dp_zero[i - 1] + Dp_zero[i - 2];
        Dp_one[i] = Dp_one[i - 1] + Dp_one[i - 2];
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int T, bigone = -1, N; cin >> T;
    vector<int> k;
    for (int i = 0; i < T; i++)
    {
        cin >> N; k.push_back(N);
        if (N > bigone)
        {
            bigone = N;
        }
    }
    Fib(bigone);
    for (int i = 0; i < k.size(); i++)
    {
        cout << Dp_zero[k[i]] << " " << Dp_one[k[i]] << "\n";
    }
}