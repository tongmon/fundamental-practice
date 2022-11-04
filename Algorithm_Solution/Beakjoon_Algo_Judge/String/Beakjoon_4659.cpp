#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/4659
문자열에서 조건대로 완전탐색하면 된다.
*/

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	unordered_set<char> v{ 'a', 'e', 'i', 'o', 'u' };
	char b;
	string y;
	while (1) {
		cin >> y;
		if (y == "end")
			break;
		int n, m, t;
		t = b = n = m = 0;
		cout << "<" << y << "> is ";
		for (auto c : y) {
			if (v.find(c) != v.end())
				t = 1, n++, m = 0;
			else
				m++, n = 0;
			if (b && b != 'e' && b != 'o' && b == c)
				b = -1;
			if (b < 0 || n == 3 || m == 3) {
				t = 0; break;
			}
			b = c;
		}
		cout << (t ? "" : "not ") << "acceptable.\n";
	}
}