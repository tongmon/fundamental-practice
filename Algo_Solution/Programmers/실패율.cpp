#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/42889
실패율 문제.
정렬을 사용하는 구현 문제다.
*/

using P = pair<float, int>;

bool Cmp(P &a, P &b) {
	if (a.first == b.first)
		return a.second < b.second;
	return a.first > b.first;
}

vector<int> solution(int N, vector<int> stages) {
	vector<P> C;
	vector<int> a, V(N + 2), W(N + 2);
	for (auto& n : stages) {
		W[n]++;
		for (int i = 1; i <= n; i++)
			V[i]++;
	}
	for (int i = 1; i <= N; i++)
		C.push_back({ V[i] ? (W[i] / (float)V[i]) : 0, i });
	sort(C.begin(), C.end(), Cmp);
	for (auto& n : C)
		a.push_back(n.second);
	return a;
}