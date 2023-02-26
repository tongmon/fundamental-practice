#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/17471
그래프가 주어지고 이 그래프 영역을 두개로 나누는데
그래프 노드마다 값이 있다.
각 영역의 값의 합을 구하고 이 차이가 가장 작게 만드는 문제.
문제가 딱 보면 쉬워보여서 초반에 후딱짜고 냈더니 틀렸다.
함정이 좀 있는데 일단 무조건 영역이 두 개여야 하기에 두 팀에는
적어도 한 개의 노드가 필요하다.
그리고 그래프가 1-2 3-4 5-6 이렇게 나뉘면 연결된 팀 2개를 만들 수가 없기에 -1
을 반환해야 한다.
이 두가지 예외상황을 고려했더니 맞았다.
DFS랑 순열을 합쳐 물어보는 문제였다.
이 문제를 통해 예외 찾는 능력을 길러간다.
*/

int Map[11][11], N, M, P[11], Vis[11], In, Min = 2e9;
unordered_set<int> TeamA, TeamB;

void Connect(int St, unordered_set<int> &Team) {
	for (auto& T : Team) {
		if (Map[T][St] && !Vis[T]) {
			Vis[T] = 1;
			Connect(T, Team);
		}
	}
}

bool Con(unordered_set<int>& Team)
{
	memset(Vis, 0, sizeof(Vis)); 
	int Cnt = 0; 
	Vis[*Team.begin()] = 1;
	Connect(*Team.begin(), Team);
	for (int i = 0; i < 11; i++)
		if (Vis[i])
			Cnt++;
	if (Cnt == Team.size())
		return 1;
	return 0;
}

void Choice(int St)
{
	if (!TeamB.empty() && !TeamA.empty() && Con(TeamA) && Con(TeamB)) {
		int A = 0;
		for (auto& T : TeamA)
			A += P[T];
		for (auto& T : TeamB)
			A -= P[T];
		Min = min(Min, abs(A));
	}
	for (int i = St; i < N; i++)
	{
		TeamA.insert(i); TeamB.erase(i);
		Choice(i + 1);
		TeamB.insert(i); TeamA.erase(i);
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++) {
		TeamB.insert(i);
		cin >> P[i];
	}
	for (int i = 0; i < N; i++) {
		cin >> M;
		for (int j = 0; j < M; j++) {
			cin >> In;
			Map[i][In - 1] = Map[In - 1][i] = 1;
		}
	}
	Choice(0);
	cout << (Min != 2e9 ? Min : -1);
}