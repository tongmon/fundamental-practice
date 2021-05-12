#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2422
*/

vector<int> S;
bool C[201][201];
int N, M, a, b, Cnt;

void func(int st, int n)
{
	if (n == 3) {
		Cnt++; return;
	}
	for (int i = st; i <= N; i++) {
		bool t = 0;
		for (auto& a : S) {
			if (C[a][i]) {
				t = 1; break;
			}
		}
		if (t) continue;
		S.push_back(i);
		func(i + 1, n + 1);
		S.pop_back();
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		C[a][b] = C[b][a] = 1;
	}
	func(1, 0);
	cout << Cnt;
}