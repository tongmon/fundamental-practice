#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/3085
완전 탐색 문제다.
한가지 주의할 점은 열과 행에서 같은 값을 연속적으로 찾는 것인데
만약 ACCCEZ여기서 C가 3개 연속으로 있다.
코드로 구하게 되면 첫번째 C = 두번째 C 이면 1 증가
두번째 C = 세번째 C 이면 1 증가 하고 끝나기에
항상 결과에 1을 더해주어야 한다.
이 문제를 통해 구현속도를 늘려간다.
*/

int N, Max;
char A[50][50];

int func(int i, int j) {
	int c = 0, r = 0, l = 0;
	for (int k = 0; k < N - 1; k++) {
		l = A[i][k] == A[i][k + 1] ? l + 1 : 0;
		c = max(l, c);
	}
	l = 0;
	for (int k = 0; k < N - 1; k++) {
		l = A[k][j] == A[k + 1][j] ? l + 1 : 0;
		r = max(l, r);
	}
	return max(r, c) + 1;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> A[i][j];
	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < N; j++)	{
			if (j != N - 1) {
				swap(A[i][j], A[i][j + 1]);
				Max = max(func(i, j + 1), max(func(i, j), Max));
				swap(A[i][j], A[i][j + 1]);
			}
			swap(A[i][j], A[i + 1][j]);
			Max = max(func(i, j), max(func(i + 1, j), Max));
			swap(A[i][j], A[i + 1][j]);
		}
	}
	cout << Max;
}