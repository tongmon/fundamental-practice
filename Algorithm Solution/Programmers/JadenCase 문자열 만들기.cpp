#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12951
JadenCase 문자열 만들기 문제.
스페이스가 나온 뒤의 문자나 첫 문자는 대문자로 그 외는 소문자로 바꾸어주면 된다.
하란대로 하면 되는 구현 문제다.
*/

string solution(string s) {
	string answer = "";
	char back = '/';
	for (int i = 0; i < s.size(); i++)
	{
		char str;
		if (!i || back == ' ')
			str = toupper(s[i]);
		else
			str = tolower(s[i]);
		back = s[i];
		answer.push_back(str);
	}
	return answer;
}