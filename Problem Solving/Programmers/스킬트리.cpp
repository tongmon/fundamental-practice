#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/49993
단순 문자열 매칭 문제.
find라는 함수를 안쓰고 있었는데 요번에 썼다.
특이한 것은 결과가 안나오는 경우 string::npos라는 스트링 클래스에 정의된 상수를 벹는다는 것이다.
이것만 유의한다면 find를 써서 숏코딩이 가능하다.
*/

int solution(string skill, vector<string> skill_trees) {
	int answer = 0, cur, bef; bool flag, nothin;
	for (int j = 0; j < skill_trees.size(); j++)
	{
		flag = 1; bef = 0; nothin = 0;
		for (int i = 0; i < skill.size() && flag; i++) {
			cur = skill_trees[j].find(skill[i]);
			if (cur == string::npos) nothin = 1;
			if ((cur != string::npos && bef > cur)
				|| (nothin && cur != string::npos)) {
				flag = 0;
			}
			if (cur != string::npos) bef = cur;
		}
		if (flag) answer++;
	}
	return answer;
}