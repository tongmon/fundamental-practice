#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/76502
괄호 회전하기 문제.
string 대신에 deque을 이용하면 좀 더 빠르게 풀린다.
*/

bool ok(deque<char> &k) {
	stack<char> S;
	for (auto& c : k) {
		char p = S.top();
		if (!S.empty() && ((c == ']' && p == '[')
			|| (c == '}' && p == '{')
			|| (c == ')' && p == '(')))
			S.pop();
		else
			S.push(c);
	}
	return S.empty();
}

int solution(string s) {
	int a = 0;
	deque<char> d(s.begin(), s.end());
	for (int i = 0; i < s.size(); i++) {
		d.push_back(d[0]);
		d.pop_front();
		a += ok(d);
	}
	return a;
}