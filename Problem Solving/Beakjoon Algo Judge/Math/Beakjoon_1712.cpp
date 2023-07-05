#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1712
수학 연산 문제다.
단순히 for문으로 접근하면 시간 초과가 발생하니 수식으로 풀어야 한다.
*/

long long A, B, C;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> A >> B >> C;
	if (B >= C) {
		cout << -1;
		return 0;
	}
	cout << A / (C - B) + 1;
}