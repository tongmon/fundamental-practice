#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/12761
간단한 BFS 문제.
최단거리여서 범위 유념하며 BFS 사용하면 된다.
*/

int V[100001], L, A, B, D, T;

int bfs() {
	V[L] = 1;
	queue<int> Q; Q.push(L);
	while (!Q.empty()) {
		T = Q.front(); Q.pop();
		if (T == D)
			break;
		int K[8] = { T - 1,T - A,T - B,T + 1,T + A,T + B,T * A,T * B };
		for (int i = 0; i < 3; i++) {
			if (K[i] >= 0 && !V[K[i]]) {
				V[K[i]] = V[T] + 1;
				Q.push(K[i]);
			}
		}
		for (int i = 3; i < 8; i++) {
			if (K[i] <= 1e5 && !V[K[i]]) {
				V[K[i]] = V[T] + 1;
				Q.push(K[i]);
			}
		}
	}
	return V[T] - 1;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> A >> B >> L >> D;
	cout << bfs();
}