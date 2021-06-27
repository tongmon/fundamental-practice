#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2470
투 포인터 문제다.
양쪽 끝에서 포인터 두 개를 시작하여 어떤게 0에 더 가까운지 이분 탐색으로 따져나간다.
그런데 다시 0보다 커진다고 루프를 종료하면 안되는 것이 -67 -1 1 66 이러면
-67 + 66 = -1 이고 -1 + 1 = 0 이라서 놓칠 수가 있다.
따라서 l < r 이를 어길 때까지 계속해서 진행하면서 최소값이 더 나오는지 봐야한다.
이 문제를 통해 구현속도를 늘려간다.
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