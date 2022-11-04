#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12916
문자열 내 p와 y의 개수 문제.
람다 함수로 문자열 순회를 했다.
*/

bool solution(string s)
{
	int a = 0;
	transform(s.begin(), s.end(), s.begin(), [&](char& c) {
		toupper(c) == 'P' ? a++ : 0;
		toupper(c) == 'Y' ? a-- : 0;
		return c;
		});
	return !a;
}