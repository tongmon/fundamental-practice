#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/5893
이진수 곱셈 문제.
1000자리의 이진수이기에 십진수 변환해서 못푼다.
난 문자열로 접근하여 풀었으나 다른 사람 풀이 중에 bitset으로 푼 사람들이 있었다.
*/

string a, Ans;

void sum(string& p, string &k) {
	string r;
	int l = p.length() - 1, kl = k.length() - 1, u = 0, A, B;
	while (0 <= kl) {
		A = p[l--] - '0', B = k[kl--] - '0';
		if ((A && B) || (!A && !B)) {
			r += u ? '1' : '0';
			u = A;
		}
		else {
			r += u ? '0' : '1';
			u = r.back() == '1' ? 0 : 1;
		}
	}
	while (l >= 0) {
		A = p[l--] - '0';
		if ((A && u) || (!A && !u)) {
			r += '0';
		}
		else {
			r += '1';
			u = 0;
		}
	}
	u ? r += '1' : r;
	reverse(r.begin(), r.end());
	p = r;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> a; Ans = a;
	for (int i = 0; i < 16; i++)
		sum(Ans, a);
	cout << Ans;
}