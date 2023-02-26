#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/16947
그래프 순환 유무 검색하는 문제다.
초반에 bfs로 구현하려했는데 잘 안되어서 dfs로 다시 구현했다.
순환은 dfs로 바로 구현하자
이 문제를 통해 구현속도를 늘려간다.
*/

int N, Vis[3001], R[3001], S, a, b;
vector<int> V[3001];

int rfind(int st, int bck)
{
	for (auto& a : V[st]) {
		if (a != bck) {
			if (S == a)
				return 1;
			if (!Vis[a]) {
				Vis[a] = 1;
				if (rfind(a, st))
					return 1;
				Vis[a] = 0;
			}
		}
	}
	return 0;
}

int bfs(int st) {
	memset(Vis, 0, sizeof(Vis));
	queue<int> Q; Vis[st] = 1;
	Q.push(st); int F = 0;
	while (!Q.empty()) {
		F = Q.front(); Q.pop();
		if (R[F]) break;
		for (auto& a : V[F]) {
			if (!Vis[a]) {
				Vis[a] = Vis[F] + 1;
				Q.push(a);
			}
		}
	}
	return Vis[F] - 1;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> a >> b;
		V[a].push_back(b);
		V[b].push_back(a);
	}
	for (int i = 1; i <= N; i++) {
		S = i;
		memset(Vis, 0, sizeof(Vis));
		Vis[i] = 1;
		R[i] = rfind(i, 0);
		Vis[i] = 0;
	}
	for (int i = 1; i <= N; i++)
		cout << bfs(i) << ' ';
}