#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/9086
문자열을 다루면 된다. 연말이라.. 간단쓰
*/

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int T;
	string s, S;
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> s;
		S = s.front(); S += s.back();
		cout << S << '\n';
	}
}