#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/15353
스트링으로 덧셈을 진행하면 된다.
*/

string sum(string &a, string &b) {
	int u = 0, k, i, j = b.size() - 1;
	string r;
	for (i = a.size() - 1; i >= 0; i--) {
		k = a[i] + (j < 0 ? '0' : b[j--]) + u - 2 * '0';
		r += (k % 10 + '0');
		u = k / 10;
	}
	if (u) r += '1';
	reverse(r.begin(), r.end());
	return r;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	string A, B;
	cin >> A >> B;
	cout << (A.size() > B.size() ? sum(A, B) : sum(B, A));
}