#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2960
에라토스테네스의 체를 오히려 비효율적으로 만들면 되는 문제다.
에라토스테네스의 체의 구현을 물어보는 문제
*/

bool Ary[1001];
int N, M, Count = 0;

int Erathos()
{
    for (int i = 2; i <= N; i = i + 2)
    {
        Ary[i] = true; Count++; 
        if (Count == M) return i;
    }
    for (int i = 3; i <= N; i = i + 2)
    {
        for (int j = i; j <= N; j = j + i)
        {
            if (Ary[j] == false) Count++;
            Ary[j] = true; 
            if (Count == M) return j;
        }
    }
}

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    cout << Erathos(); 
}