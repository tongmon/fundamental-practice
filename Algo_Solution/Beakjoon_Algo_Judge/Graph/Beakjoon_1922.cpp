#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1922
최소 스패닝 트리 문제다.
스패닝 트리에서 그리디적인 방식을 사용하기에 매 순간마다
가장 작은 값이 위로 올라오는 우선순위 큐를 이용하였다.
가장 작은 녀석은 확정적으로 방문하는 것이기에 그 정점에
다시 방문하지 않도록 방문배열에 체크를 해놓는다.
그 뒤에 그 정점과 연결된 녀석들도 갈 수 있는 후보에 추가를 해놓고
다시 현재 가장 작은 길이를 가진 녀석 찾기 반복...
이 문제를 통해 최소 스패닝 트리 구현속도를 늘려간다.
*/

using PA = pair<int, int>;
int N, M, a, b, c, Vis[1001];
vector<PA> Link[1001];

int MST(int St) {
	priority_queue<PA, vector<PA>, greater<PA>> Q;
	PA Top;
	for (auto& A : Link[St])
		Q.push({ A.first, A.second });
	int Num = 1, Min = 0; Vis[St] = 1;
	while (Num < N) {
		Top = Q.top(); Q.pop();
		if (Vis[Top.second])
			continue;
		Vis[Top.second] = 1;
		Min += Top.first;
		for (auto& A : Link[Top.second])
			Q.push({ A.first, A.second });
		Num++;
	}
	return Min;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		if (a != b) {
			Link[a].push_back({ c,b });
			Link[b].push_back({ c,a });
		}
	}
	cout << MST(1);
}