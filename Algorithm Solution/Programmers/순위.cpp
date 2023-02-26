#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/49191
그래프 문제다.
자신이 이긴 사람과 진 사람 수를 합쳐서 전체 인원 - 1 을 한 수가 나오면 순위가 확정되는 것이다.
그런데 이게 딱딱 바로 보이면 좋겠지만 전체 인원이 5명이고 
자신이 진 사람에 대한 정보가 하나 주어졌는데 이 진 사람이 4등이라면
이 사람은 진 사람 1명에 대한 정보 밖에 주어지지 않았는데도 바로 5등이 확정된다.
이렇게 딱 보이지 않고 결정되는 순위까지 모두 알아내기 위해 그래프 기법을 사용해야 한다.
일단 그래프까지 그리긴 했는데 여기서 더 나아가질 못하고 힌트를 찾아봤다... 거의 다 풀었는데 ㅆ...
내가 추가적으로 행해야할 작업은 그래프를 따라 촌이 연결되는 사람들 수를 세보는 것이였다.
이긴 사람과 진 사람 수에 대해 너비 탐색으로 연결을 따라 수를 세보고 전체 인원 - 1이면 순위가 결정된다.
이 문제를 통해 그래프에 대한 접근 능력을 길러간다.
*/

bool Vis[101];
vector<int> Lose[101], Win[101];

int BFS(int St, vector<int>* ary) {
	memset(Vis, 0, sizeof(Vis));
	queue<int> Q; int cnt = 0;
	Q.push(St); Vis[St] = 1;
	while (!Q.empty()) {
		for (auto A : ary[Q.front()]) {
			if (!Vis[A]) {
				Vis[A] = 1; Q.push(A);
				cnt++;
			}
		}
		Q.pop();
	}
	return cnt;
}

int solution(int n, vector<vector<int>> results) {
	int answer = 0;
	for (auto A : results) {
		Win[A[0]].push_back(A[1]);
		Lose[A[1]].push_back(A[0]);
	}
	for (int i = 1; i <= n; i++) {
		if (BFS(i, Lose) + BFS(i, Win) == n - 1)
			answer++;
	}
	return answer;
}