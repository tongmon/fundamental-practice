#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1059
완전탐색으로도 풀 수 있고 수학적 접근으로도 풀 수 있다.
나는 완전탐색으로 접근했다.
*/

int l, a, u;
vector<int> k, x, q;

void f(int n) {
	if (x.size() > 1) {
		if (x[0] <= u && u <= x[1])
			a++;
		return;
	}
	for (int i = n; i < q.size(); i++) {
		x.push_back(q[i]);
		f(i + 1);
		x.pop_back();
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> l;
	k.resize(l);
	for (int i = 0; i < l; i++)
		cin >> k[i];
	sort(k.begin(), k.end());
	cin >> u;
	if (k[0] > u)
		k.insert(k.begin(), 0);
	for (int i = 0; i < k.size() - 1; i++) {
		if (k[i] == u || k[i + 1] == u)
			l = 0;
		else if (k[i] < u && u < k[i + 1]) {
			l = 0;
			for (int j = k[i] + 1; j < k[i + 1]; j++)
				q.push_back(j);
			f(0);
		}
	}
	cout << a;
}