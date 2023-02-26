#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/14912
완전탐색으로 뒤적거리면 된다.
*/

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int n, k, a = 0;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		string p = to_string(i);
		for (auto& u : p)
			if (u - '0' == k)
				a++;
	}
	cout << a;
}