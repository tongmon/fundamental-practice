#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2548
나는 완전탐색을 이용하여 풀었지만 다른 풀이를 보니
그냥 정렬 후에 중간값을 찾더라...
평균을 생각하여 접근하는 문제였다.
*/

int p, N, W = 2e9, Q;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	vector<int> A(N);
	for (int i = 0; i < N; i++)
		cin >> A[i];
	Q = A[0];
	for (auto& n : A) {
		p = 0;
		for (auto& k : A)
			p += abs(n - k);
		if (W > p || (W >= p && Q > n))
			W = p, Q = n;
	}
	cout << Q;
}