#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12973
백준의 문자열 폭발과 같이 스택으로 문자열을 제거해가는 문제다.
그냥 스택 윗 부분과 들어올 녀석을 비교해서 빼줄지 아닐지 결정하면 된다.
*/

int solution(string s)
{
	stack<char> St;
	St.push(s[0]);
	for (int i = 1; i < s.size(); i++)
	{
		if (!St.empty() && St.top() == s[i])
			St.pop();
		else
			St.push(s[i]);
	}
	return St.empty();
}