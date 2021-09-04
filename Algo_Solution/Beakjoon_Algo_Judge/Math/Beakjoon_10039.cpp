#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/10039
구현 문제.
*/

int A, S;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	for (int i = 0; i < 5; i++) {
		cin >> A;
		A = A < 40 ? 40 : A;
		S += A;
	}
	cout << S / 5;
}