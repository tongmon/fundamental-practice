#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1149
DP문제..
정수삼각형 문제와 비슷한 원리로 동작한다.
각 줄마다 중복되는 색을 칠할 수 없기에 현재 선택된 색을 제외한
색을 고르는 경우 중에 제일 작은 값을 계속해서 기록해 나가면 된다.
이 문제를 통해 Dp 풀이 속도를 더 빠르게 만들어간다.
*/

int N, DP[1001][3];

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	cin >> DP[0][0] >> DP[0][1] >> DP[0][2];
	for (int i = 1; i < N; i++) {
		int Num[3];
		cin >> Num[0] >> Num[1] >> Num[2];
		DP[i][0] = min(DP[i - 1][1] + Num[0], DP[i - 1][2] + Num[0]);
		DP[i][1] = min(DP[i - 1][0] + Num[1], DP[i - 1][2] + Num[1]);
		DP[i][2] = min(DP[i - 1][0] + Num[2], DP[i - 1][1] + Num[2]);
	}
	cout << min(DP[N - 1][0], min(DP[N - 1][1], DP[N - 1][2]));
}