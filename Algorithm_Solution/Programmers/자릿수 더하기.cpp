#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12931
자릿수 더하기 문제.
람다로 숏코딩 해봤다.
*/

int solution(int n)
{
	return [&]()->int {string k = to_string(n); n = 0; for (auto& c : k) { n += (c - '0'); } return n; }();
}