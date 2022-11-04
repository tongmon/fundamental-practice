#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/17829
격자를 축소하는 문제.
격자 크기가 2의 배수인 것을 감안하여 풀면 된다.
*/

int N, A[1024][1024];

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> A[i][j];
	while (N != 1) {
		for (int i = 0, y = 0; i < N; i += 2, y++)
			for (int j = 0, x = 0; j < N; j += 2, x++) {
				int p[] = { A[i][j], A[i + 1][j],A[i][j + 1],A[i + 1][j + 1] };
				sort(p, p + 4);
				A[y][x] = p[2];
			}
		N /= 2;
	}
	cout << A[0][0];
}