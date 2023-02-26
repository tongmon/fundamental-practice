#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1248
백트래킹 문제인데 무식하게 그냥 백트래킹으로 구현하면 20^10이라는
무친 숫자가 나오기에 중간에 가지치기를 잘해야 한다.
다행이 -+0과 같이 가치를 칠 수 있는 조건이 주어지기에 이를 보고 조건에 맞다면
재귀를 진행하고 아니라면 뒤로 빼는 식으로 진행했다.
이 문제를 통해 구현속도를 늘려간다.
*/

int N, Dp[11];
char S[11][11];
vector<int> Ans;

bool func() {
	if (Ans.size() == N) {
		return 1;
	}
	for (int i = -10; i < 11; i++) {
		bool t = 1;
		Ans.push_back(i);
		for (int j = Ans.size() - 1, k = 1; j >= 0 && t; j--, k++) {
			Dp[k] = Dp[k - 1] + Ans[j];
			char s = S[j + 1][Ans.size()];
			t = ((s == '+' && Dp[k] > 0) || (s == '-' && Dp[k] < 0) || (s == '0' && !Dp[k]));
		}
		if (t) {
			if (func())
				return 1;
		}
		Ans.pop_back();
	}
	return 0;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = i; j <= N; j++) {
			cin >> S[i][j];
		}
	}
	func();
	for (auto& a : Ans) {
		cout << a << ' ';
	}
}