#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1059
*/

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int l, a = 0, u;
	cin >> l;
	vector<int> k(l);
	for (int i = 0; i < l; i++)
		cin >> k[i];
	sort(k.begin(), k.end());
	cin >> u;
	for (int i = 0; i < l - 1; i++) {
		if (k[i] == u || k[i + 1] == u)
			l = -1;
		else if (k[i] < u && u < k[i + 1]) {
			l = -1;
			a += k[i + 1] - k[i] - 2;
			if (u != k[i] + 1 && u != k[i + 1] - 1)
				a += k[i + 1] - u - 1;
		}
	}
	cout << a;
}