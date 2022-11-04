#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1916
그냥 다익스트라 문제.
다익스트라를 그냥 돌리면 된다.
*/

using Cord = pair<int, int>;

int N, M, a, b, c, Dist[1001], INF = 900000000;
vector<Cord> Vert[1001];

void Dij(int St) {
	for (int i = 1; i <= N; i++)
		Dist[i] = INF;
	priority_queue<Cord, vector<Cord>, greater<Cord>> Q;
	Dist[St] = 0; Q.push({ 0,St });
	Cord Top;
	while (!Q.empty()) {
		Top = Q.top(); Q.pop();
		if (Dist[Top.second] < Top.first)
			continue;
		for (auto A : Vert[Top.second]) {
			int buf = Top.first + A.first;
			if (buf < Dist[A.second]) {
				Dist[A.second] = buf;
				Q.push({ buf, A.second });
			}
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		Vert[a].push_back({ c,b });
	}
	cin >> a >> b;
	Dij(a); cout << Dist[b];
}