#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/77485
행렬 테두리 회전하는 문제인데 배열 테두리 회전할 때 모서리 부분 신경쓰기 싫어서
4개 빼고 회전하고 다시 끼워넣는 방식으로 구현하였다.
이 문제를 통해 구현 속도를 늘려간다.
*/

int M[101][101], k;

int Rot(vector<int> &Q) {
	int r1 = M[Q[0]][Q[1]], r2 = M[Q[0]][Q[3]], r3 = M[Q[2]][Q[1]], r4 = M[Q[2]][Q[3]],
		r = min(r1, min(r2, min(r3, r4)));
	for (int i = Q[3]; i > Q[1] + 1; i--)
		M[Q[0]][i] = M[Q[0]][i - 1], r = min(r, M[Q[0]][i]);
	for (int i = Q[1]; i < Q[3] - 1; i++)
		M[Q[2]][i] = M[Q[2]][i + 1], r = min(r, M[Q[2]][i]);
	for (int i = Q[2]; i > Q[0] + 1; i--)
		M[i][Q[3]] = M[i - 1][Q[3]], r = min(r, M[i][Q[3]]);
	for (int i = Q[0]; i < Q[2] - 1; i++)
		M[i][Q[1]] = M[i + 1][Q[1]], r = min(r, M[i][Q[1]]);
	M[Q[0]][Q[1] + 1] = r1;
	M[Q[0] + 1][Q[3]] = r2;
	M[Q[2] - 1][Q[1]] = r3;
	M[Q[2]][Q[3] - 1] = r4;
	return r;
}

vector<int> solution(int R, int C, vector<vector<int>> Q) {
	vector<int> Ans;
	for (int i = 1; i <= R; i++)
		for (int j = 1; j <= C; j++)
			M[i][j] = ++k;
	for (auto& n : Q)
		Ans.push_back(Rot(n));
	return Ans;
}