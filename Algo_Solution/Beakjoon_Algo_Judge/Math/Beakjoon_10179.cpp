#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/10179
반올림을 특정 자리에서 하기 위한 기법을 알면된다.
*/

double N, a;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	cout << fixed;
	cout.precision(2);
	for (int i = 0; i < N; i++) {
		cin >> a;
		cout << '$' << round(a * 1e2 * 0.8) / 1e2 << '\n';
	}
}