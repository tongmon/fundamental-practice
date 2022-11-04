#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/64065
튜플 문제.
숫자 문자열 집합을 받아서 정렬하면 풀리는 문제다.
한 집합 내에서도 순서가 뒤죽박죽이라 크기가 작은 집합부터
Vis 배열에 방문을 이미 한 수들을 체크하면서 올라가야 답을 구할 수 있다.
완전탐색 구현 능력을 물어보는 문제같다.
*/

bool Vis[100001];
string buffer;

vector<int> solution(string s) {
	vector<int> answer, A;
	vector<pair<int, vector<int>>> Con;
	int flag, Cnt = 0, num;
	for (int i = 1; i < s.size() - 1; i++) {
		if (s[i] == '{') {
			flag = 1;
			A.clear();
			Con.push_back({ 0,A });
		}
		if (s[i] == '}')
			flag = 0;
		if (flag && s[i] != '{') {
			if (s[i] == ',') {
				Cnt++;
				num = stoi(buffer); buffer.clear();
				Con.back().second.push_back(num);
			}
			else
				buffer += s[i];
		}
		else if (!flag) {
			i++;
			num = stoi(buffer);
			Con.back().second.push_back(num);
			Con.back().first = Cnt;
			Cnt = 0; buffer.clear();
		}
	}
	sort(Con.begin(), Con.end());
	for (auto a : Con) {
		for (auto Num : a.second) {
			if (!Vis[Num]) {
				Vis[Num] = 1;
				answer.push_back(Num);
				break;
			}
		}
	}
	return answer;
}