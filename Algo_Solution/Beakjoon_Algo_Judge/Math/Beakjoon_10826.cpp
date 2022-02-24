#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/10826
피보나치 수에다가 큰 수 연산을 곁들인 문제다.
최대치가 피보나치 10000번째이고 해당 수가 2090자리 수이기에 10000 * 2090 연산은 1억번 이하이기에
1초 이내에 풀 수가 있다.
행렬 피보나치로 풀었으면 더 빠르게 풀 수 있다.
*/

string s(string &a, string &b) {
	int u = 0, i, j, k;
	string r;
	for (i = b.size() - 1, j = a.size() - 1; i >= 0;) {
		k = u + b[i--] + a[j--] - '0' * 2;
		r += (k % 10 + '0');
		u = k / 10;
	}
	for (; j >= 0;) {
		k = u + a[j--] - '0';
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
	queue<string> q;
	q.push("0"); q.push("1");
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		q.push(s(q.back(), q.front()));
		q.pop();
	}
	cout << q.front();
}