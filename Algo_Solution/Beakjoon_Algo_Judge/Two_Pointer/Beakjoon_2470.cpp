#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2470
투 포인터 문제다.
*/

int N, t, p1, p2, x, y;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	vector<int> A(N);
	for (int i = 0; i < N; i++)
		cin >> A[i];
	sort(A.begin(), A.end());
	y = p2 = A.size() - 1;
	t = abs(A[0] + A[p2]);
	while (1) {
		int n1 = abs(A[p1 + 1] + A[p2]), n2 = abs(A[p1] + A[p2 - 1]);
		if (n1 < n2) { 
			p1++;
			if (p1 >= p2) {
				p1--; break;
			}
		}
		else {
			p2--;
			if (p1 >= p2) {
				p2++; break;
			}
		}
		if (n1 < t || n2 < t) {
			x = p1, y = p2;
			t = min(n1, n2);
		}
	}
	cout << A[x] << ' ' << A[y];
}