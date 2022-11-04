#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12978
다익스트라 문제.
다익스트라를 1번 정점에서 돌리고 그 거리결과를 보면서 시간안에
갈 수 있는 곳 개수를 세면 된다.
*/

using Cord = pair<int, int>;

int Dist[51], INF = 900000000;
vector<Cord> Vert[51];

void Dij(int st, int Size) {
	for (int i = 1; i <= Size; i++)
		Dist[i] = INF;
	priority_queue<Cord, vector<Cord>, greater<Cord>> Q;
	Dist[st] = 0; Q.push({ 0,st });
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

int solution(int N, vector<vector<int> > road, int K) {
    int answer = 0;
	for (auto A : road) {
		Vert[A[0]].push_back({ A[2],A[1] });
		Vert[A[1]].push_back({ A[2],A[0] });
	}
	Dij(1, N);
	for (int i = 1; i <= N; i++) {
		if (Dist[i] <= K)
			answer++;
	}
    return answer;
}