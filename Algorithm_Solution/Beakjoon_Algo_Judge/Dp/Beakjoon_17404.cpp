#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/17404
1번 집과 N번 집의 색상이 달라야 한다는 조건이 다른
RGB 문제다.
1번집과 N번 집의 색상을 다르게 하기 위해서는 1번집이 어떤 색으로
칠해졌는지 명확히 알아야 한다.
따라서 첫번째 색상을 명시적으로 고르고 Dp를 진행한다.
이러면 N번째의 어떤 색상이 선택되지 말아야 하는 것을 알 수가 있다.
색상 종류가 3개이기에 Dp를 3번 돌면 된다.
이 문제를 통해 Dp 구현 속도를 늘려간다.
*/

int N, Ary[3][1001], Dp[3][1001], M = 2e9;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> Ary[0][i] >> Ary[1][i] >> Ary[2][i];
	for (int i = 0; i < 3; i++) {
		Dp[i][1] = 1e9; 
		Dp[(i + 1) % 3][1] = 1e9;
		Dp[(i + 2) % 3][1] = Ary[(i + 2) % 3][1];
		for (int j = 2; j <= N; j++) {
			Dp[0][j] = min(Dp[1][j - 1], Dp[2][j - 1]) + Ary[0][j];
			Dp[1][j] = min(Dp[0][j - 1], Dp[2][j - 1]) + Ary[1][j];
			Dp[2][j] = min(Dp[0][j - 1], Dp[1][j - 1]) + Ary[2][j];
		}
		M = min(min(M, Dp[(i + 1) % 3][N]), Dp[i][N]);
	}
	cout << M;
}