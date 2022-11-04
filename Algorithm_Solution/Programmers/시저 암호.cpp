#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12926
시저 암호 문제.
나머지 연산 이용하면 풀린다.
*/

string solution(string s, int n) {
	string ans = "";
	for (auto& c : s) {
		if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
			ans += 'a' <= c && c <= 'z' ? ('a' + (c - 'a' + n) % 26) : ('A' + (c - 'A' + n) % 26);
		else ans += c;
	}
	return ans;
}