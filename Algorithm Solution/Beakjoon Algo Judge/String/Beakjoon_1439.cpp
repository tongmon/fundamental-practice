#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1439
0, 1로 구성된 구역을 나누어 개수를 센 뒤에 더 작은 것을 반환하면 된다.
*/

int l, p[2];
string a;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> a;
	l = a[0] - '0'; p[l]++;
	for (auto& c : a)
		if (c - '0' != l)
			p[l = c - '0']++;
	cout << min(p[0], p[1]);
}