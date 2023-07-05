#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/5555
반지에 적힌 문자열이라 다시 돌아서 원점으로 돌아올 수 있기에 문자열을 한번 더 붙이면 된다.
*/

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	string p, s;
	int n, a = 0;
	cin >> p >> n;
	for (int i = 0; i < n; i++) {
		cin >> s;
		s += s;
		s.find(p) != string::npos ? a++ : 0;
	}
	cout << a;
}