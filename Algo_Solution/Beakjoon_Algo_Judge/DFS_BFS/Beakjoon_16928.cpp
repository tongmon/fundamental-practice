#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/16928
bfs로 최단거리를 구하는 문제다.
실수할 수 있는 것이 사다리나 뱀이 있을 경우 무조건 그것을 타야한다는 것이다.
사다리나 뱀이 없을 경우에만 주사위가 굴려진 대로 이동이 가능하다.
이 문제를 통해 실수를 줄여간다.
*/

int N, M, V[101], a, b;
unordered_map<int, int> L;

void BFS() {
	queue<int> Q;
	Q.push(1); V[1] = 1;
	while (!Q.empty()) {
		int F = Q.front();
		if (F == 100)
			break;
		Q.pop();
		for (int i = 1; i < 7; i++) {
			int n = F + i;
			if (n > 100) continue;
			if (L.find(n) != L.end() && !V[L[n]]) {
				V[L[n]] = V[F] + 1;
				Q.push(L[n]);
			}
			else if (L.find(n) == L.end() && !V[n]) {
				V[n] = V[F] + 1;
				Q.push(n);
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < N + M; i++) {
		cin >> a >> b;
		L[a] = b;
	}
	BFS();
	cout << V[100] - 1;
}