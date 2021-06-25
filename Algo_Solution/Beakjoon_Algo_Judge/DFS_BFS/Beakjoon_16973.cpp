#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/16973
bfs 문제인데 시간초과를 조심해야 한다.
직사각형을 움직일 때 직사각형 내부에 1이 있는지 없는지 전체를 검사할 필요가 없고
왼쪽으로 가면 새로 다가가는 영역만 체크해야 한다.
그러면 이중 포문에서 단일 포문으로 계산이 줄어들어 시간초과를 피할 수 있다.
이 문제를 통해 실수를 줄여간다.
*/

int N, M, A[1001][1001], Vis[1001][1001], H, W, sx, sy, dx, dy,
X[4] = { 0,1,0,-1 }, Y[4] = { 1,0,-1,0 };

int bfs() {
	queue<pair<int, int>> Q;
	Q.push({ sx,sy }); Vis[sy][sx] = 1;
	pair<int, int> T;
	while (!Q.empty()) {
		T = Q.front(); Q.pop();
		if (T.first == dx && T.second == dy)
			return Vis[dy][dx] - 1;
		for (int i = 0; i < 4; i++) {
			int nx = T.first + X[i], ny = T.second + Y[i], f = 1;
			if (!(0 < nx && nx + W - 1 <= M && 0 < ny && ny + H - 1 <= N && !Vis[ny][nx]))
				continue;
			if (!i) {
				for (int j = nx; j < nx + W && f; j++) {
					if (A[ny + H - 1][j]) f = 0;
				}
			}
			else if (i == 1) {
				for (int j = ny; j < ny + H && f; j++) {
					if (A[j][nx + W - 1]) f = 0;
				}
			}
			else if (i == 2) {
				for (int j = nx; j < nx + W && f; j++) {
					if (A[ny][j]) f = 0;
				}
			}
			else {
				for (int j = ny; j < ny + H && f; j++) {
					if (A[j][nx]) f = 0;
				}
			}
			if (f) {
				Q.push({ nx,ny });
				Vis[ny][nx] = Vis[T.second][T.first] + 1;
			}
		}
	}
	return -1;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			cin >> A[i][j];
	cin >> H >> W >> sy >> sx >> dy >> dx;
	cout << bfs();
}