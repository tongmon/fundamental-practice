#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/4673
각 자리 숫자를 찾을 수 있으면 된다.
*/

int b[90001];

int func(int n) {
	int r = 0, k = n;
	while (n) {
		r += n % 10;
		n /= 10;
	}
	return r + k;
}

int main() 
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	for (int i = 1; i < 10001; i++)
		b[func(i)] = 1;
	for (int i = 1; i < 10001; i++) {
		if (!b[i]) cout << i << '\n';
	}
}