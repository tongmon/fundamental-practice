#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/3372
사각형 위에서 아래로 내려오면서 더하는 dp 문제인데 정답 숫자의 크기가 터무니 없이 크기에
BigInt 덧셈 구현이 필요하다.
구현해서 풀었다.
*/

string A[101][101];
int N, M[101][101];

string add(string& a, string& b) {
	string c;
	int i = b.size() - 1, j = a.size() - 1, u = 0;
	for (; i >= 0; i--, j--) {
		int A = a[j] - '0', B = b[i] - '0';
		c += ('0' + (A + B + u) % 10);
		u = (A + B + u) / 10;
	}
	while (j >= 0) {
		int A = a[j] - '0';
		c += ('0' + (A + u) % 10);
		u = (A + u) / 10;
		j--;
	}
	if (u) c += '1';
	reverse(c.begin(), c.end());
	return c;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			cin >> M[i][j];
			A[i][j] = "0";
		}
	A[0][0] = '1';
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!M[i][j] || A[i][j] == "0")
				continue;
			if (j + M[i][j] < N)
				A[i][j + M[i][j]] = A[i][j + M[i][j]].size() > A[i][j].size() ? add(A[i][j + M[i][j]], A[i][j]) : add(A[i][j], A[i][j + M[i][j]]);
			if (i + M[i][j] < N)
				A[i + M[i][j]][j] = A[i + M[i][j]][j].size() > A[i][j].size() ? add(A[i + M[i][j]][j], A[i][j]) : add(A[i][j], A[i + M[i][j]][j]);
		}
	}
	cout << A[N - 1][N - 1];
}