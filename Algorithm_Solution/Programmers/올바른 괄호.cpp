#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12909
올바른 괄호 문제
기본적인 스택 문제이다.
스택의 최상단이 ( 이고 들어올 값이 ) 이면 ( ) 쌍이기 때문에
걍 스택에 넣을 이유가 없어 ( ) 를 날려버린다.
이 짓을 계속하면 올바른 괄호 묶음이였다면 마지막에 스택에 아무것도 없을 것이고
아니면 스택에 원소가 남아있을 것이다.
*/

bool solution(string s)
{
	bool answer = true;
	stack<char> St;
	for (int i = 0; i < s.size(); i++) {
		if (!St.empty() && St.top() == '(' && s[i] == ')')
			St.pop();
		else
			St.push(s[i]);
	}
	if (!St.empty())
		answer = 0;
	return answer;
}