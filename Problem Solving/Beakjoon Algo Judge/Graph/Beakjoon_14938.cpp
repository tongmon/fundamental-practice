#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/14938
다익스트라를 모든 정점에 대해서 돌려도 풀리고
아싸리 플로이드 와샬로 돌려도 풀린다.
시간 복잡도를 비교해보면 다익스트라가 좀 더 빠를 것이다.
나는 다익스트라 연습 해볼겸 다익스트라로 풀었다.
다익스트라 돌리고 구해진 해당 점점의 Dist를 보고 거기에 갈 수 있으면
아이템을 집고 아니면 안 집고 이렇게 진행해주면 풀린다.
이 문제를 통해 다익스트라에 대한 숙련도를 높여간다.
*/

using Cord = pair<int, int>;

int N, M, R, a, b, c, Max, item[101], Dist[101], INF = 99999;
vector<Cord> vert[101];

void Dij(int St) {
	priority_queue<Cord, vector<Cord>, greater<Cord>> Q;
	for (int i = 1; i <= N; i++)
		Dist[i] = INF;
	Q.push({ 0,St }); Dist[St] = 0;
	Cord Top;
	while (!Q.empty()) {
		Top = Q.top(); Q.pop();
		if (Dist[Top.second] < Top.first)
			continue;
		for (auto ve : vert[Top.second]) {
			int buf = Top.first + ve.first;
			if (Dist[ve.second] > buf) {
				Dist[ve.second] = buf;
				Q.push({ buf, ve.second });
			}
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M >> R;
	for (int i = 1; i <= N; i++)
		cin >> item[i];
	for (int i = 0; i < R; i++)
	{
		cin >> a >> b >> c;
		vert[a].push_back({ c,b });
		vert[b].push_back({ c,a });
	}
	for (int i = 1; i <= N; i++) {
		int Sum = 0; Dij(i);
		for (int j = 1; j <= N; j++) {
			if (Dist[j] <= M)
				Sum += item[j];
		}
		Max = max(Sum, Max);
	}
	cout << Max;
}