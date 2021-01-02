#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/49189
가장 먼 노드 문제.
그래프 문제여서 BFS, DFS 등을 떠올릴 수 있고 거리에 관련되기에
다익스트라 BFS등을 선택할 수 있다.
일단 거쳐가는 간선 개수가 많을 수록 먼것이기에 그냥 간선 길이가 1이라고 하는
그래프에서 다익스트라를 돌리고 가장 먼 노드들을 찾아 개수를 세면된다.
사실 길이가 모두 같아서 BFS로 그냥 돌려도 상관없는데 나는 다익스트라가 먼저 떠올라
그냥 그대로 갔다.
*/

using Cord = pair<int, int>;
vector<Cord> Vert[20001];
int Dist[20001], INF = 9000000, Max;

void Dij(int n) {
	priority_queue<Cord, vector<Cord>, greater<Cord>> Q;
	Dist[1] = 0; Q.push({ 0,1 });
	for (int i = 2; i <= n; i++)
		Dist[i] = INF;
	Cord Top;
	while (!Q.empty()) {
		Top = Q.top(); Q.pop();
		if (Dist[Top.second] < Top.first)
			continue;
		for (auto A : Vert[Top.second]) {
			int buf = Top.first + A.first;
			if (Dist[A.second] > buf) {
				Dist[A.second] = buf;
				Q.push({ buf, A.second });
			}
		}
	}
}

int solution(int n, vector<vector<int>> edge) {
	int answer = 0;
	for (auto A : edge) {
		Vert[A[0]].push_back({ 1, A[1] });
		Vert[A[1]].push_back({ 1, A[0] });
	}
	Dij(n);
	for (int i = 1; i <= n; i++) {
		if (Dist[i] != INF)
			Max = max(Dist[i], Max);
	}
	for (int i = 1; i <= n; i++) {
		if (Max == Dist[i])
			answer++;
	}
	return answer;
}