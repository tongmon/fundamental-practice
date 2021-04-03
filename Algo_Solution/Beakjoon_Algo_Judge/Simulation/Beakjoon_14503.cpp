#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/14503
구현 문제다.
문제에 쓰여있는데도 구현하면 된다.
바라보고 있는 방향에서 왼쪽 방향으로 탐색 순서를 정해주었기 때문에
방향에 따라 달라지는 인덱스 처리를 위한 배열을 따로 두고 이를 참조해 순회하였다.
이 문제를 통해 구현속도를 늘려간다.
*/

int N, M, D, cY, cX, Map[51][51], Cnt, Di[4][2] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} },
Ind[4][4] = { {0,1,2,3}, {3,0,1,2}, {2,3,0,1}, {1,2,3,0} };

void Operate(int y, int x, int Dir);

void Clean(int y, int x, int Dir) {
	if (!Map[y][x]) {
		Map[y][x] = 2;
		Cnt++;
	}
	Operate(y, x, Dir);
}

void Operate(int y, int x, int Dir) {
	int A[4][2], is_End = 1, is_Back = 1;
	for (int i = 0; i < 4; i++) {
		A[i][0] = y + Di[Ind[Dir][i]][0], A[i][1] = x + Di[Ind[Dir][i]][1];
		if (!Map[A[i][0]][A[i][1]])
			is_End = 0;
		if (i == 1 && Map[A[i][0]][A[i][1]] == 1)
			is_Back = 0;
	}
	if (is_End) {
		if (is_Back)
			Operate(A[1][0], A[1][1], Dir);
		else
			return;
	}
	else if (!Map[A[0][0]][A[0][1]])
		Clean(A[0][0], A[0][1], !Dir ? 3 : Dir - 1);
	else if (Map[A[0][0]][A[0][1]])
		Operate(y, x, !Dir ? 3 : Dir - 1);
}