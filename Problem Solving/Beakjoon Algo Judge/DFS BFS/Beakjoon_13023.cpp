#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/13023
깊이 탐색 문제다.
안으로 파고드는 레벨이 3까지기에 시간복잡도는 문제없다.
이 문제를 통해 구현속도를 늘려간다.
*/

vector<int> A[2000];
int V[2000], N, M, a, b;

bool func(int st, int n) {
	if (n == 3) {
		for (auto& e : A[st]) {
			if (!V[e])
				return 1;
		}
		return 0;
	}
	for (auto& e : A[st]) {
		if (V[e]) continue;
		V[e] = 1;
		if (func(e, n + 1))
			return 1;
		V[e] = 0;
	}
	return 0;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		A[a].push_back(b);
		A[b].push_back(a);
	}
	for (int i = 0; i < N; i++) {
		V[i] = 1;
		if (func(i, 0)) {
			cout << 1; return 0;
		}
		V[i] = 0;
	}
	cout << 0;
}