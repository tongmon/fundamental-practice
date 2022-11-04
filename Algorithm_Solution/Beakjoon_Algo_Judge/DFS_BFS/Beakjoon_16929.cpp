#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/16929
그래프에서 사이클을 판단하는 문제다.
전 좌표와 현재 좌표를 토대로 왔던 길을 다시 되돌아가지 않을 수 있고
현재 좌표에서 다음에 갈 좌표를 선택했는데 방문을 한 상태라면 사이클을 의심해볼 수 있다.
여기서 사이클 크기 조건과 부합하면 사이클이 된다.
이 문제를 통해 구현속도를 늘려간다.
*/

int N, M, V[51][51], X[4] = { 1,0,-1,0 }, Y[4] = { 0,1,0,-1 };
char A[51][51], K;

bool func(int x, int y, int bx, int by, int cnt)
{
	for (int i = 0; i < 4; i++) {
		int nx = X[i] + x, ny = Y[i] + y;
		if ((nx != bx || ny != by) && 0 <= nx && nx < M
			&& 0 <= ny && ny < N && K == A[ny][nx]) {
			if (V[ny][nx] && cnt > 2)
				return 1;
			if (!V[ny][nx]) {
				V[ny][nx] = 1;
				bool b = func(nx, ny, x, y, cnt + 1);
				V[ny][nx] = 0;
				if (b) return b;
			}
		}
	}
	return 0;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> A[i][j];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			K = A[i][j];
			V[i][j] = 1;
			if (func(j, i, -1, -1, 0)) {
				cout << "Yes"; return 0;
			}
			V[i][j] = 0;
		}
	cout << "No";
}