#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1026
그냥 A는 순정렬 B는 역정렬 한 후에 같은 인덱스 끼리 곱하면 되는 기초 정렬문제
*/

#pragma warning(disable:4996)

int N;
int A[51], B[51], Ans = 0;

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    for (int i = 0; i < N; i++)
    {
        cin >> B[i];
    }
    sort(A, A + N); sort(B, B + N, greater<int>());
    for (int i = 0; i < N; i++)
    {
        Ans = Ans + A[i] * B[i];
    }
    cout << Ans;
}