#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2303
for문 3번 돌려도 되는 완전탐색 문제.
재귀로 풀면 깔끔해진다.
*/

int N, K[5], M;
vector<pair<int, int>> A;

void sel(int n, int s, int c) {
	if (c == 3) {
		M = max(M, s % 10);
		return;
	}
	for (int i = n; i < 5; i++)
		sel(i + 1, s + K[i], c + 1);
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++) {
		M = 0;
		for (int j = 0; j < 5; j++)
			cin >> K[j];
		sel(0, 0, 0);
		A.push_back({ M,i + 1 });
	}
	sort(A.begin(), A.end());
	cout << A[N - 1].second;
}