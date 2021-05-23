#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2210
갔던 곳을 또 갈 수 있는 완전탐색 문제다.
5x5이기에 시간복잡도는 충분하다.
*/

int A[5][5], X[4] = { 1,0,-1,0 }, Y[4] = { 0,1,0,-1 };
string P;
unordered_set<string> V;

void func(int x, int y)
{
	if (P.length() == 6) {
		V.insert(P);
		return;
	}
	for (int i = 0; i < 4; i++) {
		int nx = X[i] + x, ny = Y[i] + y;
		if (0 <= nx && nx < 5 && 0 <= ny && ny < 5) {
			P.push_back(A[ny][nx] + '0');
			func(nx, ny);
			P.pop_back();
		}
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			cin >> A[i][j];
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			P.push_back(A[i][j] + '0');
			func(j, i);
			P.pop_back();
		}
	cout << V.size();
}