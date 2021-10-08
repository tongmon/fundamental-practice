#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/10211
연속적인 부분합을 구하는 문제.
주어지는 수가 음수라 투 포인터로 접근이 안되고 브루트 포스로 풀어야 한다.
*/

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int T, N, M, S;
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> N;
		vector<int> K(N);
		for (int j = 0; j < N; j++)
			cin >> K[j];
		M = -2e9;
		for (int j = 1; j <= N; j++) {
			M = max(M, S = accumulate(K.begin(), K.begin() + j, 0));
			for (int k = 1; k + j - 1 < N; k++)
				M = max(M, S = S - K[k - 1] + K[k + j - 1]);
		}
		cout << M << '\n';
	}
}