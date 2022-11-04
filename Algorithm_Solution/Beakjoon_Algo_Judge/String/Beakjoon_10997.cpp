#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/10997
뱅글뱅글 돌기에 별찍는 방향을 전환해주면서 그려가는 방식을 택했다.
이 문제를 통해 구현속도를 늘려간다.
*/

int N, x, y, X[4] = { 0,1,0,-1 }, Y[4] = { 1,0,-1,0 };
string L[400], buf, s;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	if (N == 1) {
		cout << '*';
		return 0;
	}
	for (int i = 0; i < 5 + (N - 2) * 4; i++) {
		buf += ' ';
		s += '*';
	}
	L[0] = s;
	for (int i = 1; i < buf.size() + 2; i++)
		L[i] = buf;
	x = y = 0;
	int i = 0, k = buf.size() + 1;
	while (k) {
		for (int j = 0; j < k; j++) {
			x += X[i % 4], y += Y[i % 4];
			L[y][x] = '*';
		}
		for (int j = 0; j < k - 2; j++) {
			x += X[(i + 1) % 4], y += Y[(i + 1) % 4];
			L[y][x] = '*';
		}
		i += 2; k -= 2;
	}
	for (int p = 0; p < buf.size() + 2; p++) {
		while (L[p].back() == ' ') {
			L[p].pop_back();
		}
		cout << L[p] << '\n';
	}
}