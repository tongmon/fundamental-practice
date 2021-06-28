#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2636
공기가 바깥부터 오기 때문에 제일 외각 지역을 한번씩 돌면서
dfs를 하고 닿는 치즈가 있는지 검사하면 된다.
이렇게 닿는 치즈가 있으면 없애주면서 반복해주면 풀린다.
이 문제를 통해 구현 속도를 늘려간다.
*/

int N, M, A[101][101], V[101][101], T, bC, C, X[4] = { 0,0,1,-1 }, Y[4] = { 1,-1,0,0 };

void dfs(int x, int y) {
	for (int i = 0; i < 4; i++)
	{
		int nx = x + X[i], ny = y + Y[i];
		if (0 <= nx && nx < M && 0 <= ny && ny < N && !V[ny][nx]) {
			V[ny][nx] = 1;
			if (A[ny][nx]) {
				A[ny][nx] = 0; C++;
			}
			else
				dfs(nx, ny);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> A[i][j];
	do {
		bC = C;
		C = 0;
		for (int i = 0; i < M; i++) {
			if (!V[0][i]) {
				V[0][i] = 1; dfs(i, 0);
			}
		}
		for (int i = 0; i < M; i++) {
			if (!V[N - 1][i]) {
				V[N - 1][i] = 1; dfs(i, N - 1);
			}
		}
		for (int i = 0; i < N; i++) {
			if (!V[i][0]) {
				V[i][0] = 1; dfs(0, i);
			}
		}
		for (int i = 0; i < N; i++) {
			if (!V[i][M - 1]) {
				V[i][M - 1] = 1; dfs(M - 1, i);
			}
		}
		T++;
		memset(V, 0, sizeof(V));
	} while (C);
	cout << T - 1 << '\n' << bC;
}