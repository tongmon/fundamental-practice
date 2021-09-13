#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12930
이상한 문자 만들기 문제.
람다 함수를 사용하여 숏코딩을 해봤다.
*/

string solution(string s) {
	int i = 0;
	transform(s.begin(), s.end(), s.begin(), 
		[&i](char c)-> char 
		{
			if (c == ' ') 
			{ 
				i = 0; 
				return c; 
			}
			return (++i % 2 ? toupper(c) : tolower(c));
		});
	return s;
}