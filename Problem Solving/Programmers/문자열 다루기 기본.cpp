#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12918
문자열 다루기 기본 문제.
isdigit() 이라는 문자가 숫자인지 판별하는 함수를 알아간다.
*/

bool solution(string s) {
	if (s.size() == 4 || s.size() == 6)
		return isdigit(*min_element(s.begin(), s.end())) && isdigit(*max_element(s.begin(), s.end()));
	return 0;
}