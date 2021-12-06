#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1032
주어지는 스트링의 길이가 같이에 이중포문 돌면서 비교해주면 된다.
*/

int N;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	vector<string> A(N + 1);
	for (int i = 0; i < N; i++)
		cin >> A[i];
	for (int i = 0, j; i < A[0].length(); i++) {
		char b = A[0][i];
		for (j = 1; j < N && b == A[j][i]; j++)
			b = A[j][i];
		A[N].push_back(j == N ? b : '?');
	}
	cout << A[N];
}