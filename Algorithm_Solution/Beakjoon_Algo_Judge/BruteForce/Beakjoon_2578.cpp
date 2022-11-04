#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2578
빙고 문제
완전탐색으로 접근하면 쉽게 풀린다.
*/

int M[5][5], A, S, s, k = 1, C;
unordered_map<int, pair<int, int>> B;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			cin >> M[i][j];
			B[M[i][j]] = { i,j };
		}
	for (; k < 26; k++) {
		cin >> A;
		M[B[A].first][B[A].second] = 0;
		C = S = 0;
		for (int j = 0; j < 5; j++) S += M[j][j];
		if (!S) C++;
		S = 0;
		for (int j = 0, p = 4; j < 5; j++, p--) S += M[j][p];
		if (!S) C++;
		for (int p = 0; p < 5; p++) {
			S = s = 0;
			for (int j = 0; j < 5; j++) {
				S += M[j][p];
				s += M[p][j];
			}
			if (!S) C++;
			if (!s) C++;
		}
		if (C > 2) break;
	}
	cout << k;
}