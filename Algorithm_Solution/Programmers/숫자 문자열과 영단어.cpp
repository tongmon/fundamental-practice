#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/81301
숫자 문자열과 영단어 문제.
난 해쉬맵으로 풀었지만 regex_replace를 이용해 깔끔하게 푼 풀이도 있었다.
스트링 나오면 정규식 한번쯤 고민할만 하다.
이 문제를 통해 구현속도를 늘려간다.
*/

unordered_map<string, string> ston;

int solution(string s) {
	string answer;
	ston["zero"] = '0'; ston["one"] = '1'; ston["two"] = '2'; ston["three"] = '3';
	ston["four"] = '4'; ston["five"] = '5'; ston["six"] = '6'; ston["seven"] = '7';
	ston["eight"] = '8'; ston["nine"] = '9';
	string buf;
	for (int i = 0; i < s.size(); i++)
	{
		if ('0' <= s[i] && s[i] <= '9') {
			answer += ston[buf];
			buf.clear();
			answer += s[i];
		}
		else
			buf += s[i];
		if (ston.find(buf) != ston.end()) {
			answer += ston[buf];
			buf.clear();
		}
	}
	answer += ston[buf];
	return stoi(answer);
}