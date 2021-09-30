#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/14490
정규식 연습 좀 했다.
*/

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	string s;
	smatch m;
	cin >> s;
	regex_search(s, m, regex(":"));
	int k = stoi(m.prefix().str()), t = stoi(m.suffix().str()), x;
	x = k > t ? gcd(k, t) : gcd(t, k);
	cout << k / x << ':' << t / x;
}