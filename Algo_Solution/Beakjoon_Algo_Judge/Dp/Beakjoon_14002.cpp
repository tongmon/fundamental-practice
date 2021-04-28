#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/14002
가장 긴 부분 수열을 찾는 문제에서 인덱스를 저장해주는 배열을 따로두어
역추적을 해주면 되는 문제다.
이 문제를 통해 구현속도를 늘려간다.
*/

int N, ML, St, Dp[1001], A[1001], I[1001];
deque<int> Ans;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> A[i];
	for (int i = 0; i < N; i++) {
		int L = 0, k = -1;
		for (int j = 0; j < i; j++) {
			if (A[j] < A[i] && L < Dp[j]) {
				L = Dp[j];
				k = j;
			}
		}
		Dp[i] += L + 1;
		I[i] = k;
		if (Dp[i] > ML) {
			ML = Dp[i];
			St = i;
		}
	}
	while (St != -1) {
		Ans.push_front(A[St]);
		St = I[St];
	}
	cout << ML << '\n';
	for (auto& k : Ans)
		cout << k << ' ';
}