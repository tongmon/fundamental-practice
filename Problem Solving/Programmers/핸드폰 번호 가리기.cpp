#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12948
핸드폰 번호 가리기 문제.
람다식을 활용해서 풀었다.
*/

string solution(string p) {
	int i = 0;
	transform(p.begin(), p.end(), p.begin(), [&](char& c)->char {return p.size() - 4 > i++ ? '*' : c; });
	return p;
}