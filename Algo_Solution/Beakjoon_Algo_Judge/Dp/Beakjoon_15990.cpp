#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/15990
연속해서 같은 수를 사용할 수는 없기에 어떤 수로 시작하는지가 중요하다.
2 + 3... 아니면 1 + 2... 이렇게 시작 번호 2, 1을 따로 분리해서 저장해야 한다.
이 문제를 통해 Dp 구현 속도를 늘려간다.
*/

long long T, N, Dp[100001][4], M = 1000000009;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> T;
	Dp[1][1] = Dp[2][2] = Dp[3][1] = Dp[3][2] = Dp[3][3] = 1;
	for (int i = 4; i < 100001; i++) {
		Dp[i][1] = (Dp[i - 1][2] + Dp[i - 1][3]) % M;
		Dp[i][2] = (Dp[i - 2][1] + Dp[i - 2][3]) % M;
		Dp[i][3] = (Dp[i - 3][1] + Dp[i - 3][2]) % M;
	}
	for (int i = 0; i < T; i++)	{
		cin >> N;
		cout << (Dp[N][1] + Dp[N][2] + Dp[N][3]) % M << '\n';
	}
}