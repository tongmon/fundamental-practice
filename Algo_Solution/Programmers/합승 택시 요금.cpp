#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/72413
합승 택시 요금 문제.
다익스트라를 이용해 풀면된다.
일단 어느 지점까지 합승을 해야만 최소값이 도출된다면
그니까 예를 들어 5에서 a,b가 같이 출발하여 1을 거친후 흩어져
각자의 목적지로 가는 루트가 최소라면 5에서 1까지 가는 최소거리 구하고
1에서 a의 목적지까지 가는 최소거리, 1에서 b의 목적지까지 가는 최소거리를 구하면 되는 것이다.
그러면 각 정점에서 다익스트라를 돌려 최소 거리를 구해놓고 
Dist[a] + Dist[b] + 출발지부터 합승하는 곳까지 최소 거리 이 식을 풀어서 최소 값을 찾아내면 된다.
이 문제를 통해 그래프 문제에 대한 감을 키워간다.
*/

using Cord = pair<int, int>;
int Dist[201], ODist[201], INF = 999999999;
vector<Cord> Vert[201];

void Dij(int St, int N)
{
	priority_queue<Cord, vector<Cord>, greater<Cord>> Q;
	for (int i = 0; i <= N; i++)
		Dist[i] = INF;
	Dist[St] = 0;
	Q.push({ 0, St });
	Cord Top;
	while (!Q.empty()) {
		Top = Q.top();
		Q.pop();
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

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
	for (auto A : fares) {
		Vert[A[1]].push_back({ A[2], A[0] });
		Vert[A[0]].push_back({ A[2], A[1] });
	}
	Dij(s, n);
	int Min = Dist[a] + Dist[b];
	memcpy(ODist, Dist, sizeof(Dist));
	for (int i = 1; i <= n; i++)
	{
		Dij(i, n);
		int buf = Dist[a] + Dist[b] + ODist[i];
		if(buf > 0)
			Min = min(buf, Min);
	}
	return Min;
}