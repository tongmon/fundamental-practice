#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/16194
Dp 는 Dp[현재 카드 장수] = 최소 가격 을 나타낸다.
이렇게 만드려면 다음 Dp 값을 얻을 때 몇 장이 들었는지에 따라
가격이 달라지는 카드 가격을 이용해야 한다.
예를 들어 카드 1장에 대한 가격 + Dp[카드 3장], 카드 2장에 대한 가격 + Dp[카드 2장]
이렇게 반복해서 Dp[4장] 최솟값을 획득할 수 있다.
이 문제를 통해 Dp 구현속도를 늘려간다.
*/

int N, Ary[1001], Dp[1001];

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> Ary[i];
	for (int i = 1; i <= N; i++) {
		Dp[i] = 1e9;
		for (int j = 1; j < i; j++)
			Dp[i] = min(Dp[i - j] + Ary[j], Dp[i]);
		Dp[i] = min(Ary[i], Dp[i]);
	}
	cout << Dp[N];
}