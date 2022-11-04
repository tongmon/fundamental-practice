#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12947
하샤드 수 문제.
숏코딩을 위해 transform을 사용했다.
*/

bool solution(int x) {
	string s = to_string(x);
	int p = 0;
	transform(s.begin(), s.end(), s.begin(), [&](char& c)->char { return p += c - '0'; });
	return x % p ? 0 : 1;
}