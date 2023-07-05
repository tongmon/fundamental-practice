#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1904
기본 DP 문제.
맨 끝이 1인 경우, 맨 끝이 00인 경우 나누어서 생각해보면
피보나치와 같은 결과가 나온다.
*/

int N, Dp[1000001] = { 0,1,2 };

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 3; i <= N; i++)
	{
		Dp[i] = Dp[i - 1] + Dp[i - 2];
		Dp[i] %= 15746;
	}
	cout << Dp[N];
}