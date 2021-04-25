#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12939
최댓값과 최솟값 문제.
스트링을 숫자로 변환만 해주고 비교하면 된다.
그냥 구현 문제다.
*/

string solution(string s) {
	string answer = "", buf;
	long long Min = 1e18, Max = -1e18, num;
	for (auto &c : s) {
		if (c == ' ') {
			num = stoi(buf);
			Min = min(num, Min);
			Max = max(num, Max);
			buf.clear();
		}
		else
			buf.push_back(c);
	}
	num = stoi(buf);
	Min = min(num, Min);
	Max = max(num, Max);
	answer += to_string(Min) + ' ' + to_string(Max);
	return answer;
}