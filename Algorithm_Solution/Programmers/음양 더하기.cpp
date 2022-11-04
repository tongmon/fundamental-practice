#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/76501?language=cpp
음양 더하기 문제.
주어진 배열을 순회하면서 조건대로 더하면 된다.
*/

int solution(vector<int> absolutes, vector<bool> signs) {
	int answer = 0;
	for (int i = 0; i < signs.size(); i++)
		answer += signs[i] ? absolutes[i] : -1 * absolutes[i];
	return answer;
}