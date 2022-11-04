#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/15661
두 팀을 나누는 문제다.
팀 하나를 유니크하게 정하면 나머지 팀은 알아서 결정된다.
이 문제를 통해 구현 속도를 늘려간다.
*/

int N, A[21][21], Sum, Min = 2e9;
unordered_set<int> L, R;

void func(int St, int T, int S) {
	Min = min(Min, abs(T - S));
	for (int i = St; i <= N; i++) {
		int K = 0, P = 0;
		for (auto& a : L)
			K += A[a][i] + A[i][a];
		L.insert(i); R.erase(i);
		for (auto& a : R)
			P += A[a][i] + A[i][a];
		func(i + 1, T + K, S - P);
		L.erase(i); R.insert(i);
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 1; i <= N; i++) {
		R.insert(i);
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
			Sum += A[i][j];
		}
	}
	func(1, 0, Sum);
	cout << Min;
}