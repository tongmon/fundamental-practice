#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/5800
정렬하고 순회하면 된다.
*/

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int T, N;
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> N;
		vector<int> A(N);
		int M = -1;
		for (int j = 0; j < N; j++)
			cin >> A[j];
		sort(A.begin(), A.end(), greater<int>());
		for (int j = 1; j < N; j++)
			M = max(M, A[j - 1] - A[j]);
		cout << "Class " << i + 1 << "\nMax " << A[0] << ", Min " << A.back() << ", Largest gap " << M << '\n';
	}
}