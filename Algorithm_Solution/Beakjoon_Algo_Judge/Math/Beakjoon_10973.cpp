#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/10973
이전 순열을 구하는 문제.
prev_permutation이라는 함수를 쓰면 풀린다.
난 이 함수를 몰라가지고 순서를 거꾸로하고 next_permutation을 취했다.
이 문제를 통해 prev_permutation 함수를 알아간다.
*/

int A[10001], N, In;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> In;
		A[i] = N - In + 1;
	}
	if (!next_permutation(A, A + N))
		cout << -1;
	else
		for (int i = 0; i < N; i++)
			cout << N + 1 - A[i] << ' ';
}