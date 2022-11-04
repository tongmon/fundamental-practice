#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1238
최단경로 문제.
최단 경로 문제인데 최적화가 중요하다.
모든 경로에서 X로 가는 최단 경로를 찾아야하고
반대로! X에서 모든 경로로 가는 최단 경로를 알아야 한다.
X에서 모든 경로로 가는 최단 경로는 X를 시작점으로 다익스트라를 돌리면 획득이 가능하다.
그런데 모든 경로에서 X로 가는 최단 경로는 비효율적인 방식으로 하자면
모든 정점에서 다익스트라를 돌리면 되지만 불필요하게 X 가 2라고 하면 1에서 2까지의 최단 경로만
구하면 되는 것을 1에서 3 까지 가는 정보까지 얻게 되고 이 과정에서 불필요한 연산이 더 들어간다.
물론 이렇게 다익스트라를 계속 돌려도 시간 복잡도가 1000000log(1000)이라 1초안에 연산이 가능하다.
하지만 더 효율적으로 할 수 있는 방법이 있는데 반대로 생각해보면 된다.
만약 이 문제가 단방향 그래프가 아니라 양방향이였다면 그냥 X를 시작점으로 다익스트라를 돌리면 오고 가는
최단 거리가 한방에 다 구해졌을 것이다.
이 문제는 단방향 그래프이기에 X에서 갈 때는 평소 대로 다익스트라를 돌리고
X로 올 때는 역방향 경로를 미리 구해놓고 그것을 이용한 다익스트라를 돌린다.
역방향을 쓰는 이유는 오는 것을 가는 것으로 생각하고 다익스트라를 돌리면 특정 정점에 도착하는
모든 정점에 대한 최단 경로를 알 수가 있기 때문이다.
이를 명심하고 잘 써먹자.
*/

using Cord = pair<int, int>;

int N, M, X, St, End, T, Dist[1001], xDist[1001], INF = 900000, Max;
vector<Cord> Vert[1001], rVert[1001];

void Dij(int st, int *dist, vector<Cord> *ary) {
	for (int i = 1; i <= N; i++)
		dist[i] = INF;
	priority_queue<Cord, vector<Cord>, greater<Cord>> Q;
	dist[st] = 0; Q.push({ 0, st });
	Cord Top;
	while (!Q.empty()) {
		Top = Q.top(); Q.pop();
		if (dist[Top.second] < Top.first)
			continue;
		for (auto ve : ary[Top.second]) {
			int buf = ve.first + Top.first;
			if (dist[ve.second] > buf) {
				dist[ve.second] = buf;
				Q.push({ buf,ve.second });
			}
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M >> X;
	for (int i = 0; i < M; i++) {
		cin >> St >> End >> T;
		Vert[St].push_back({ T, End });
		rVert[End].push_back({ T, St });
	}
	Dij(X, Dist, Vert);
	Dij(X, xDist, rVert);
	for (int i = 1; i <= N; i++)
		Max = max(Max, Dist[i] + xDist[i]);
	cout << Max;
}

/*
* 처음에 접근한 방식인 다익스트라 여러번, 비효율적
using Cord = pair<int, int>;

int N, M, X, St, End, T, Dist[1001], xDist[1001], INF = 900000;
vector<Cord> Vert[1001];

void Dij(int st) {
	for (int i = 1; i <= N; i++)
		Dist[i] = INF;
	priority_queue<Cord, vector<Cord>, greater<Cord>> Q;
	Dist[st] = 0; Q.push({ 0, st });
	Cord Top;
	while (!Q.empty()) {
		Top = Q.top(); Q.pop();
		if (Dist[Top.second] < Top.first)
			continue;
		for (auto ve : Vert[Top.second]) {
			int buf = ve.first + Top.first;
			if (Dist[ve.second] > buf) {
				Dist[ve.second] = buf;
				Q.push({ buf,ve.second });
			}
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M >> X;
	for (int i = 0; i < M; i++) {
		cin >> St >> End >> T;
		Vert[St].push_back({ T, End });
	}
	Dij(X); memcpy(xDist, Dist, sizeof(Dist));
	int Max = 0;
	for (int i = 1; i <= N; i++) {
		Dij(i);
		Max = max(Max, Dist[X] + xDist[i]);
	}
	cout << Max;
}
*/