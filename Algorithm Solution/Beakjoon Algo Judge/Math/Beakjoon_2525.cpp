#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2525
수학 문제다. 나머지 연산을 활용하면 시계를 만들 수 있다.
*/

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int n, m, t, q;
	cin >> n >> m >> t;
	q = m + t % 60;
	cout << ((n + t / 60) % 24 + q / 60) % 24 << ' ' << q % 60;
}