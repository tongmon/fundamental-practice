#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2755
소수점 반올림에 관한 문제다.
3째자리에서 반올림하려면 100을 곱한후 round를 취한뒤
100을 나누면 된다.
*/

double N, k, f = 4.3, q, Ans;
unordered_map<string, double> A;
string t, p, u = "A ";
char z[3] = { '+','0','-' };

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			u[1] = z[j];
			A[u] = f;
			f -= 0.3;
		}
		u[0] += 1;
		f -= 0.1;
	}
	for (int i = 0; i < N; i++) {
		cin >> t >> k >> p;
		Ans += A[p] * k;
		q += k;
	}
	Ans = round(Ans / q * 1e2) / 1e2;
	cout << fixed;
	cout.precision(2);
	cout << Ans;
}