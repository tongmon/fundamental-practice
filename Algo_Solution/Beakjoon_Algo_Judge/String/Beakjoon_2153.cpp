#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2153
소수찾기를 알면 된다.
*/

bool is_p(int n) {
	if (n == 1) return 1;
	if (!(n % 2)) return 0;
	for (int i = 3; i <= sqrt(n); i += 2) {
		if (!(n % i)) return 0;
	}
	return 1;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int K[200], j = 1, a = 0;
	string s;
	for (int i = 0; i < 26; j++)
		K['a' + i++] = j;
	for (int i = 0; i < 26; j++)
		K['A' + i++] = j;
	cin >> s;
	for (auto& c : s)
		a += K[c];
	cout << (is_p(a) ? "It is a prime word." : "It is not a prime word.");
}