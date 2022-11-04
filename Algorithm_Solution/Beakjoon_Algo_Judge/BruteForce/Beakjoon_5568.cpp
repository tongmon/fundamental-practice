#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/5568
완전탐색 문제다.
수를 고르라는데로 고르고 기록해가면 된다.
*/

int N, K;
vector<int> A;
unordered_set<string> V;
string p;

void sel(int n) {
	if (n == K) {
		V.insert(p);
		return;
	}
	for (int i = 0; i < A.size(); i++) {
		int l = to_string(A[i]).size(), b = A[i];
		p += to_string(A[i]);
		A.erase(A.begin() + i);
		sel(n + 1);
		A.insert(A.begin() + i, b);
		for (int j = 0; j < l; j++)
			p.pop_back();
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> K;
	A.resize(N);
	for (int i = 0; i < N; i++)
		cin >> A[i];
	sel(0);
	cout << V.size();
}