#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/84512
모음사전 문제.
모든 경우의 수가 4000여개가 안되어 완전탐색 방식으로 해결하였다.
*/

string K = "XAEIOU", P;
vector<string> A;
auto f = [](string& b)->void { for (int i = 5 - b.length(); i > 0; i--) b += '0'; };

void func(int n) {
	if (!P.empty()) {
		string b = P;
		f(b);
		A.push_back(b);
	}
	if (n == 5) return;
	for (int i = 1; i < 6; i++) {
		P += (i + '0');
		func(n + 1);
		P.pop_back();
	}
}

int solution(string W) {
	func(0);
	unordered_map<char, char> V;
	V['A'] = '1'; V['E'] = '2'; V['I'] = '3'; V['O'] = '4'; V['U'] = '5';
	for (auto& c : W) c = V[c];
	f(W);
	int r = 0;
	while (A[r++] != W) {}
	return r;
}