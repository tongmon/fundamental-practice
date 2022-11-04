#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/15988
1,2,3만을 사용하여 더해 숫자를 만드는 문제다.
4를 만드는 경우에 1 + 3, 3 + 1을 다르게 보기 때문에
첫빠따로 1을 사용하는 경우 2를 사용하는 경우 3을 사용하는 경우
이렇게 나누어보면 풀린다.
따라서 점화식은 Dp[i] = Dp[i-3] + Dp[i-2] + Dp[i-1] 이게 된다.
이 문제를 통해 구현속도를 늘려간다.
*/

using ll = long long;
ll T, N, Dp[1000001] = { 0,1,2,4 }, M = 1000000009;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> T;
	for (ll i = 4; i <= 1e6; i++)
		Dp[i] = (Dp[i - 1] + Dp[i - 2] + Dp[i - 3]) % M;
	while (T--) {
		cin >> N;
		cout << Dp[N] << '\n';
	}
}