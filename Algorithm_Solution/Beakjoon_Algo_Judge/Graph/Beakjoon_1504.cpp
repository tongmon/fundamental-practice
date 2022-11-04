#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1504
다익스트라를 여러번 돌려야하는 문제다.
문제에서 1 -> v1 -> v2 -> N, 1 -> v2 -> v1 -> N을 하는 것을 요구하니
이대로 다익스트라를 돌리면 된다.
이 문제를 통해 다익스트라에 대한 이해도를 높이고 구현을 통해 상기를 시켰다.
*/

using Cord = pair<int, int>;

int N, E, Dist[801], v1, v2, c, v1d, v2d, INF = 99999999;
vector<Cord> Vert[801];

void Dji(int St) {
	for (int i = 1; i <= N; i++)
		Dist[i] = INF;
	priority_queue<Cord, vector<Cord>, greater<Cord>> Q;
	Q.push({ 0,St }); Dist[St] = 0;
	Cord Top;
	while (!Q.empty()) {
		Top = Q.top(); Q.pop();
		if (Dist[Top.second] < Top.first)
			continue;
		for (auto Ver : Vert[Top.second]) {
			int buf = Ver.first + Top.first;
			if (Dist[Ver.second] > buf) {
				Dist[Ver.second] = buf;
				Q.push({ buf, Ver.second });
			}
		}
	}
}

int Ans(int ve1, int ve2, int dist) {
	int ans = dist;
	if (ans == INF)
		return ans;
	Dji(ve1);
	if (Dist[ve2] == INF)
		return INF;
	ans += Dist[ve2];
	Dji(ve2);
	if (Dist[N] == INF)
		return INF;
	ans += Dist[N];
	return ans;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> E;
	for (int i = 0; i < E; i++)
	{
		cin >> v1 >> v2 >> c;
		Vert[v1].push_back({ c, v2 });
		Vert[v2].push_back({ c, v1 });
	}
	cin >> v1 >> v2;
	Dji(1); v1d = Dist[v1]; v2d = Dist[v2];
	int re1 = Ans(v1, v2, v1d), re2 = Ans(v2, v1, v2d);
	if (re1 == re2 && re1 == INF)
		cout << -1;
	else if (re2 > re1)
		cout << re1;
	else
		cout << re2;
}