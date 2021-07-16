#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2822
정렬을 적절히 하면 풀린다.
*/

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	vector<pair<int, int>> A;
	set<int> B;
	int k;
	for (int i = 0; i < 8; i++) {
		cin >> k;
		A.push_back({ k,i + 1 });
	}
	sort(A.begin(), A.end(), greater<pair<int, int>>());
	k = 0;
	for (int i = 0; i < 5; i++) {
		k += A[i].first;
		B.insert(A[i].second);
	}
	cout << k << '\n';
	for (auto& n : B)
		cout << n << ' ';
}