#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/16948
전형적인 최단 거리를 bfs로 구하는 문제다.
*/

int N, a, b, c, d, V[201][201], X[6] = { -2,-2,0,0,2,2 }, Y[6] = { -1,1,-2,2,-1,1 };

int bfs()
{
	queue<pair<int, int>> Q;
	Q.push({ a,b }); V[a][b] = 1;
	while (!Q.empty()) {
		pair<int, int> F = Q.front();
		Q.pop();
		for (int i = 0; i < 6; i++) {
			int nx = X[i] + F.first, ny = Y[i] + F.second;
			if (nx == c && ny == d)
				return V[F.first][F.second];
			if (0 <= nx && nx < N && 0 <= ny && ny < N && !V[nx][ny]) {
				V[nx][ny] = V[F.first][F.second] + 1;
				Q.push({ nx,ny });
			}
		}
	}
	return -1;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> a >> b >> c >> d;
	cout << bfs();
}