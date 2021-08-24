#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2910
수의 크기가 아닌 빈도로 정렬해주면 된다.
빈도로 정렬하기에 map과 pair를 이용했다.
*/

using P = pair<int, int>;
int N, C, n;
unordered_set<int> V;
unordered_map<int, P> rM;
map<P, int, greater<P>> M;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> C;
	C = N;
	for (int i = 0; i < N; i++) {
		cin >> n;
		if (V.find(n) == V.end()) {
			V.insert(n);
			rM[n] = { 1,C-- };
		}
		else rM[n].first++;
	}
	for (auto& m : rM)
		M[{m.second.first, m.second.second}] = m.first;
	for (auto& m : M)
		for (int k = 0; k < m.first.first; k++)
			cout << m.second << ' ';
}