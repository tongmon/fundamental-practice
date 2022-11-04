#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1309
타일링 DP 문제.
나는 수식으로 푼 것 같지만 이게 의도는 아닌것 같고
밑에 설명한 것 처럼 3가지 케이스로 나누어서 DP를 활용해 푸는 것이
알고리즘적인 사고를 키우는데 좋은 것이다.
DP를 오랜만에 풀어서 그런지 가물가물 한데 케이스 나누어서 이차원배열로
DP 짜는 시간을 단축해야겠다.
*/

int N, DP[100001], K = 5;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	DP[1] = 3; DP[2] = 7;
	for (int i = 3; i <= N; i++) {
		DP[i] = (DP[i - 1] + K * 2) % 9901;
		K += DP[i - 1]; K %= 9901;
		
		// 내가 사용한 방식과 동일한 논리... 찾기만 하면 쉽다. 찾기가 까다로워서 그렇지
		// DP[i] = DP[i - 1] * 2 + DP[i - 2];
		
		// 좀더 DP 적인 방식... 일단 타일링 문제에서 접근하던 것과 같이 
		// 위쪽 타일만 있는거, 아래쪽 타일만 있는거, 타일 없는거로 3분해서 생각한다.
		// 타일을 연속으로 놓을 수 없기에 타일이 없는 경우는 0, 1, 2 케이스를 모두 더하지만
		// 타일이 하나라도 깔려 있는 것들은 자신 옆에 놓는 경우를 제외해주고 더해주어야 한다.
		// DP[i][0] = DP[i - 1][0] + DP[i - 1][1] + DP[i - 1][2];
		// DP[i][1] = DP[i - 1][0] + DP[i - 1][2]
		// DP[i][2] = DP[i - 1][0] + DP[i - 1][1]
	}
	cout << DP[N];
}

/*
int N, Dp[100001][3];

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	Dp[1][0] = Dp[1][1] = Dp[1][2] = 1;
	for (int i = 2; i <= N; i++) {
		Dp[i][0] = Dp[i - 1][0] + Dp[i - 1][1] + Dp[i - 1][2];
		Dp[i][1] = Dp[i - 1][2] + Dp[i - 1][0];
		Dp[i][2] = Dp[i - 1][1] + Dp[i - 1][0];
		for (auto& A : Dp[i])
			A %= 9901;
	}
	cout << (Dp[N][0] + Dp[N][1] + Dp[N][2]) % 9901;
}
*/