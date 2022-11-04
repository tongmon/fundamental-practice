#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1092
*/

int N, M, C, K, Ans;
vector<int> S;
multiset<int, greater<int>> B;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	S.resize(N);
	for (int i = 0; i < N; i++) 
		cin >> S[i];
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> K;
		B.insert(K);
	}
	sort(S.begin(), S.end(), greater<int>());
	if (S[0] < *B.begin()) {
		cout << -1; return 0;
	}
	while (!B.empty()) {
		int f = 0;
		for (auto& n : B) {
			if (n <= S[C]) {
				C++; B.erase(B.find(n)); f = 1;
				break;
			}
		}
		if (C == N || !f || B.empty()) {
			Ans++; C = 0;
		}
	}
	cout << Ans;
}