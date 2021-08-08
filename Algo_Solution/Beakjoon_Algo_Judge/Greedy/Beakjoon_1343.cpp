#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1343
그리디 알고리즘 문제다.
AAAA를 붙이냐 BB를 붙이냐 고민을 해보면 된다.
이 문제를 통해 구현 속도를 늘려간다.
*/

string A, X, B;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> A;
	for (int i = 0; i <= A.size(); i++) {
		if (i == A.size() || A[i] == '.') {
			if (X.size() % 6 && X.size() % 2) {
				cout << -1;
				return 0;
			}
			for (int j = 0; j < X.size(); j += 4) {
				if (j + 2 == X.size()) {
					B += "BB";
					break;
				}
				else B += "AAAA";
			}
			if (i != A.size()) B += '.';
			X.clear();
		}
		else X += 'X';
	}
	cout << B;
}