#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/3055
bfs 문제다.
물은 여러개 주어질 수 있고 두더지는 한마리가 주어지는데
나는 물과 두더지 모두 하나만 주어지는 줄알고 초반에 고생했다.
문제를 똑바로 읽는 습관을 들이자.
이 문제를 통해 나의 해이해진 문제 읽기 능력을 바로 잡았다.
*/

int N, M, V[51][51], X[4] = { 1,-1,0,0 }, Y[4] = { 0,0,1,-1 }, a, b;
char A[51][51];
queue<tuple<int, int, int>> Q;

#define isin(x, y) (0 <= x && x < M && 0 <= y && y < N)

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			cin >> A[i][j];
			if (A[i][j] == 'S') {
				a = i, b = j;
			}
			if (A[i][j] == '*') {
				V[i][j] = -1;
				Q.push({ i,j,-1 });
			}
		}
	V[a][b] = 1;
	Q.push({ a,b,0 });
	while (!Q.empty()) {
		int x = get<1>(Q.front()), y = get<0>(Q.front()), n = get<2>(Q.front());
		Q.pop();
		if (n >= 0 && A[y][x] == 'D') {
			cout << n; return 0;
		}
		for (int i = 0; i < 4; i++) {
			int ny = y + Y[i], nx = x + X[i];
			if (n < 0) {
				if (isin(nx, ny) && A[ny][nx] != 'X' && A[ny][nx] != 'D' && V[ny][nx] >= 0) {
					V[ny][nx] = -1;
					Q.push({ ny,nx,-1 });
				}
			}
			else {
				if (isin(nx, ny) && A[ny][nx] != 'X' && A[ny][nx] != '*' && !V[ny][nx]) {
					V[ny][nx] = 1;
					Q.push({ ny,nx,n + 1 });
				}
			}
		}
	}
	cout << "KAKTUS";
}