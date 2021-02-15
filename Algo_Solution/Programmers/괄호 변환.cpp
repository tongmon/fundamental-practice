#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/60058
괄호 변환 문제.
구현을 어떻게 하라는 지시사항이 명확해서 그대로 구현하면 된다.
올바른 문자열인지 판단하는 과정은 스택을 이용하여 판단한다.
오직 ( -- ) 이 경우에만 스택에서 문자를 제거하게 되고 나머지는 스택에
문자를 넣게 된다.
이 문제를 통해 문자열 처리 구현 속도를 늘려간다.
*/

void Subseq(string &w)
{
	string u, Con;
	if (w.empty())
		return;
	int oCnt = 0, cCnt = 0, i = 0;
	for (; i < w.size() && ((!oCnt && !cCnt) || oCnt != cCnt); i++)
	{
		if (w[i] == '(')
			oCnt++;
		else
			cCnt++;
		u.push_back(w[i]);
		if (!Con.empty() && Con.back() == '(' && w[i] == ')')
			Con.pop_back();
		else
			Con.push_back(w[i]);
	}
	string v(w.begin() + i, w.end());
	Subseq(v);
	if (!Con.empty()) {
		w = "(" + v + ")";
		for (int i = 1; i < (int)u.size() - 1; i++) {
			if (u[i] == '(')
				w += ")";
			else
				w += "(";
		}
	}
	else
		w = u + v;
}

string solution(string p) {
	Subseq(p);
	return p;
}