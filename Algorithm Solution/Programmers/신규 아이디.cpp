#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/72410
신규 아이디 문제.
문제에서 하란 대로 구현하면 된다.
머리 비우고 타자 치다보면 풀 수 있다.
*/

string solution(string new_id) {
	string answer = "";
	for (auto &str : new_id) {
		str = tolower(str);
	}
	for (auto str : new_id) {
		if (('a' <= str && str <= 'z') || str == '.' || str == '_' || str == '-' || ('0' <= str && str <= '9'))
			answer.push_back(str);
	}
	new_id.clear();
	char back = ' ';
	for (auto str : answer) {
		new_id.push_back(str);
		if (back == str && back == '.')
			new_id.pop_back();
		back = str;
	}
	if (new_id[0] == '.')
		new_id.erase(new_id.begin());
	if (new_id.back() == '.')
		new_id.pop_back();
	if (new_id.empty())
		new_id = 'a';
	if (new_id.size() > 15) {
		string buf;
		for (int i = 0; i < 15; i++)
			buf.push_back(new_id[i]);
		if (buf.back() == '.')
			buf.pop_back();
		new_id = buf;
	}
	if (new_id.size() <= 2) {
		char t = new_id.back();
		while (new_id.size() != 3) {
			new_id.push_back(t);
		}
	}
	return new_id;
}