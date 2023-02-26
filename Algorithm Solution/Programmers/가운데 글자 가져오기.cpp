#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12903
가운데 글자 가져오기 문제.
짝수 길이, 홀수 길이를 나누어 접근하면 된다.
*/

string solution(string s) {
	int i = s.length();
	return s.substr(i % 2 ? i / 2 : i / 2 - 1, i % 2 ? 1 : 2);
}