#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/10546
해쉬맵을 사용하여 풀면 된다.
속도 향상을 위한 공간 예약을 사용한다면 더 빠른 속도로 풀 수 있다.
*/

int N;
string K;
unordered_map<string, int> M;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	M.reserve(2e5);
	for (int i = 0; i < N; i++) {
		cin >> K;
		M[K]++;
	}
	for (int i = 1; i < N; i++) {
		cin >> K;
		M[K]--;
	}
	for (auto& p : M) {
		if (p.second) {
			cout << p.first; break;
		}
	}
}