#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/16940
주어진 bfs가 맞는지 확인하는 문제.
set을 통해 한번에 확인하고 확인한 녀석들을 지워가며 탐색하면 된다.
bfs 특성상 현재 연결된 정점들을 모두 큐에 넣게 되기에
넣는 시점에서 하나라도 넣을 필요가 없는 정점이 존재한다면 주어진 bfs 경로는
틀린 경로가 된다.
이 문제를 통해 구현 속도를 늘려간다.
*/

int N, I, a, b;
vector<int> A;
unordered_set<int> G[100001];

bool bfs() {
	queue<int> Q;
	if (A[I++] != 1)
		return 0;
	Q.push(1);
	while (!Q.empty()) {
		int T = Q.front(), S = G[T].size(); Q.pop();
		while (I < N && G[T].find(A[I]) != G[T].end()) {
			Q.push(A[I]);
			G[A[I]].erase(T);
			S--; I++;
		}
		if (S)
			return 0;
	}
	return 1;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N - 1; i++) {
		cin >> a >> b;
		G[a].insert(b);
		G[b].insert(a);
	}
	A.resize(N);
	for (int i = 0; i < N; i++)
		cin >> A[i];
	cout << bfs();
}