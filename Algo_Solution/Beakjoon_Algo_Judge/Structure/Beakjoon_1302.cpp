#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1302
해쉬맵을 사용하면 접근이 쉬워진다.
*/

int T;
string A;
unordered_map<string, int> M;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> A;
		if (M.find(A) == M.end())
			M[A] = 0;
		M[A]++;
	}
	T = 0; A = "~";
	for (auto& K : M) {
		if (T < K.second) {
			A = K.first;
			T = K.second;
		}
		if (T == K.second)
			A = min(A, K.first);
	}
	cout << A;
}