#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/42861
섬 연결하기 문제.
문제가 낯이 익어서 곰곰히 생각해보니 최소비용 스패닝 트리 생성문제였다.
기억을 짜맞추어 계속해서 최단 거리만 골라 스패닝 트리를 만드는 짓을 하는
코드를 구현했더니 맞았다.
다른 사람의 풀이법을 보니 내 방식은 Prim 알고리즘이고
유니온 파인드로 간선을 통해 트리 생성하는 방식은 kruskal 방식이란다.
이 문제를 통해 최소 비용 스패닝 트리를 생성하는 방식을 상기하고 간다.
*/

using Cord = pair<int, int>;
vector<Cord> Vert[101];
bool Vis[101];

int Prim(int St, int n)
{
	int Cnt = 1, Ans = 0;
	priority_queue<Cord, vector<Cord>, greater<Cord>> Q;
	for (auto A : Vert[St])
		Q.push({ A.first,A.second });
	Vis[St] = 1;
	while (Cnt != n) {
		Cord Top = Q.top();
		Q.pop();
		if (Vis[Top.second])
			continue;
		Vis[Top.second] = 1;
		Cnt++;
		Ans += Top.first;
		for (auto A : Vert[Top.second])
			Q.push({ A.first,A.second });
	}
	return Ans;
}

int solution(int n, vector<vector<int>> costs) {
	int answer = 0;
	for (auto C : costs) {
		Vert[C[0]].push_back({ C[2],C[1] });
		Vert[C[1]].push_back({ C[2],C[0] });
	}
	answer = Prim(0, n);
	return answer;
}