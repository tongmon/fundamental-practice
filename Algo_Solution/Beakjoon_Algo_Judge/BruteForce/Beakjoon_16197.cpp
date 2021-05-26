#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/16197
격자 탐색 문제인데 시작점이 두개이고 움직일 때 같이 움직인다.
따라서 방문 배열을 각 시작점마다 다른 배열에 두어 둘다 방문한 지점이면
다시 방문할 필요가 없다고 판단하고 두 동전 중 하나라도 바닥에 떨어졌으면
버튼 누른 수를 세는 식으로 풀었다.
이 문제를 통해 구현속도를 늘려간다.
*/

#define IsIn(x, y) (0 <= (x) && (x) < M && 0 <= (y) && (y) < N)

using Co = pair<int, int>;
int N, M, Ans = 1e9, V[21][21][2], X[4] = { 0,0,1,-1 }, Y[4] = { -1,1,0,0 };
vector<Co> C;
char A[21][21];

void func(Co C1, Co C2, int cnt)
{
	if (cnt > Ans || cnt > 10)
		return;
	for (int i = 0; i < 4; i++) {
		int x1 = C1.first + X[i], y1 = C1.second + Y[i],
			x2 = C2.first + X[i], y2 = C2.second + Y[i];
		if (IsIn(x1, y1) && A[y1][x1] == '#')
			y1 = C1.second, x1 = C1.first;
		if (IsIn(x2, y2) && A[y2][x2] == '#')
			y2 = C2.second, x2 = C2.first;
		if (IsIn(x1, y1) && IsIn(x2, y2) && (!V[y1][x1][0] || !V[y2][x2][1])) {
			int b1 = V[y1][x1][0], b2 = V[y1][x1][1];
			V[y1][x1][0] = V[y1][x1][1] = 1;
			func({ x1,y1 }, { x2,y2 }, cnt + 1);
			V[y1][x1][0] = b1, V[y1][x1][1] = b2;
		}
		else if ((IsIn(x1, y1) && !IsIn(x2, y2))
			|| (!IsIn(x1, y1) && IsIn(x2, y2))) {
			Ans = min(Ans, cnt);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			cin >> A[i][j];
			if (A[i][j] == 'o') {
				C.push_back({ j,i });
				V[i][j][C.size() - 1] = 1;
			}
		}
	func(C[0], C[1], 1);
	cout << (Ans == 1e9 ? -1 : Ans);
}