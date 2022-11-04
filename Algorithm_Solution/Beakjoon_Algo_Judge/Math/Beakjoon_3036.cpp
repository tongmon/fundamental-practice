#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/3036
�ִ������� ã�� �� �˸� ���� Ǯ �� �ִ�.
*/

int R, r[101];

int gcd(int a, int b) {
	if (!b) return a;
	return gcd(b, a % b);
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> R;
	for (int i = 0; i < R; i++)
		cin >> r[i];
	for (int i = 1; i < R; i++) {
		int G = r[0] > r[i] ? gcd(r[0], r[i]) : gcd(r[i], r[0]);
		cout << r[0] / G << "/" << r[i] / G << "\n";
	}
}