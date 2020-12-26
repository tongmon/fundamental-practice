#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1389
BFS로 큐가 비게될 때까지 모든 정점을 찍고 시작점에서 다른 모든 정점까지의 거리를 구하는 문제이다.
플로이드 와샬 알고리즘이라고도 한다. (뭐 이건 보통 3중 포문으로 돌리지만 난 BFS로 돌리는게 편하다)
그래서 경로 거리의 합잉 가장 낮은 사람의 번호를 출력하면 된다.
BFS가 최적 거리의 정점들 부터 찍어나간다는 성질을 알고 있다면 원활이 풀 수 있다.
*/

int N, M, who, rel, Min = 10000, mwho, Vis[101];
vector<int> Vert[101];

void BFS(int St) {
	memset(Vis, 0, sizeof(Vis));
	queue<int> Q; Q.push(St); Vis[St] = 1;
	int Fr, Ans = 0;
	while (!Q.empty()) {
		Fr = Q.front();
		for (auto Fri : Vert[Fr]) {
			if (!Vis[Fri]) {
				Vis[Fri] = Vis[Fr] + 1;
				Ans += Vis[Fri] - 1;
				Q.push(Fri);
			}
		}
		Q.pop();
	}
	if (Min > Ans) {
		Min = Ans;
		mwho = St;
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> who >> rel;
		Vert[who].push_back(rel);
		Vert[rel].push_back(who);
	}
	for (int i = 1; i <= N; i++)
		BFS(i);
	cout << mwho;
}