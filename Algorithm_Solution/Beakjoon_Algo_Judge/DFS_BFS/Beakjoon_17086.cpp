#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/17086
기본적인 bfs 문제.
모든 칸에서 1에 대한 최단 경로를 구해주고 비교해보면 된다.
이 문제를 통해 구현속도를 늘려간다.
*/

int dX[8] = { 0,0,1,-1,1,-1,1,-1 }, dY[8] = { 1,-1,1,-1,-1,1,0,0 }, W, H, M[51][51], V[51][51], A;

int bfs(int x,int y) {
	memset(V, 0, sizeof(V));
	queue<pair<int, int>> Q;
	V[y][x] = 1;
	Q.push({ y,x });
	int X, Y;
	while (!Q.empty()) {
		Y = Q.front().first, X = Q.front().second;
		Q.pop();
		if (M[Y][X]) break;
		for (int i = 0; i < 8; i++) {
			int cx = X + dX[i], cy = Y + dY[i];
			if (0 <= cx && cx < W && 0 <= cy && cy < H && !V[cy][cx]) {
				V[cy][cx] = V[Y][X] + 1;
				Q.push({ cy,cx });
			}
		}
	}
	return V[Y][X] - 1;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> H >> W;
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)	{
			cin >> M[i][j];
		}
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++) {
			A = max(A, bfs(j, i));
		}
	cout << A;
}