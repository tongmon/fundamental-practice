#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/11779
다익스트라를 이용하는데 그 최단 경로가 어떻게 생겨먹은지 알아야하는 문제다
플로이드 와샬의 백트래킹 방식과 동일하게 배열에 자신이 거치게 되는
바로 앞 정점을 저장해놓고 최종적으로 역으로 계속 따라가면 경로의
역순을 얻게된다.
이 경로의 역순을 출력만 정방향으로 해주면 답이 된다.
이 문제를 통해 다익스트라에 대한 이해력을 높인다.
*/

using Cord = pair<int, int>;
vector<Cord> Vert[1001];
int N, M, a, b, c, INF = 200000000, Dist[1001], Track[1001];

void Dij(int St) {
	priority_queue<Cord, vector<Cord>, greater<Cord>> Q;
	for (int i = 1; i <= N; i++)
		Dist[i] = INF;
	Dist[St] = 0; Q.push({ 0,St }); Track[St] = -1;
	Cord Top;
	while (!Q.empty()) {
		Top = Q.top(); Q.pop();
		if (Dist[Top.second] < Top.first)
			continue;
		for (auto &A : Vert[Top.second]) {
			int buf = Top.first + A.first;
			if (buf < Dist[A.second]) {
				Dist[A.second] = buf;
				Track[A.second] = Top.second;
				Q.push({ buf,A.second });
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
	Dij(a);
	cout << Dist[b] << '\n';
	deque<int> way;
	while (b != -1) {
		way.push_front(b);
		b = Track[b];
	}
	cout << way.size() << '\n';
	for (auto A : way)
		cout << A << ' ';
}