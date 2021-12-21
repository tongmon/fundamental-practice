#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/9996
정규식 regex_match를 이용하면 된다.
*/

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	string r, s;
	int T, K;
	cin >> T;
	cin >> r;
	K = r.find('*');
	r = "^(" + r.substr(0, K) + ").*(" + r.substr(K + 1) + ")$";
	for (int i = 0; i < T; i++) {
		cin >> s;
		cout << (regex_match(s, regex(r)) ? "DA\n" : "NE\n");
	}
}