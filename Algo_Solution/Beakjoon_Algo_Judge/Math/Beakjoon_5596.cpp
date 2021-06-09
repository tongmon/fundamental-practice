#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/5596
덧셈하는 문제.
*/

int a, s, p;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	for (int i = 0; i < 8; i++) {
		cin >> a;
		i < 4 ? s += a : p += a;
	}
	cout << max(s, p);
}