#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/13398
중간에 숫자를 한번 삭제할 수 있다는 점이 약간 골치아프게 했지만
그 여부를 따져 따로 저장하는 방식으로 해결했다.
수열에서 숫자를 제거하지 않고 이어가는 방식은 현재 부터 새로 시작했을 때가 큰지
아니면 과거에서 이어져온 수에 자신을 더한 것이 더 큰지를 따진다.
수열에서 숫자를 한 번 제거한 경우를 따질 때는 현재 숫자를 거르는 경우 아니면
예전에 한 번 제거했던 경우에서 현재 숫자를 더한 경우 이렇게 둘 중에 큰 것이 선택된다.
이러한 가짓수를 따져가며 제일 큰 녀석을 찾으면 된다.
이 문제를 통해 Dp 실력을 길러간다.
*/

using ll = long long;
ll N, Ary[100001], Dp[100001][2], M;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (ll i = 1; i <= N; i++)
		cin >> Ary[i];
	M = Dp[1][0] = Dp[1][1] = Ary[1];
	for (ll i = 2; i <= N; i++) {
		Dp[i][0] = Ary[i] + max(Dp[i - 1][0], (ll)0);
		Dp[i][1] = max(Dp[i - 1][0], Dp[i - 1][1] + Ary[i]);
		M = max(M, max(Dp[i][0], Dp[i][1]));
	}
	cout << M;
}