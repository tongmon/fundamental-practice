#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/42862
체육복 문제.
탐욕적으로 맨 앞에서 빌릴 수 있는 사람한테 먼저 빌리면 알아서 최적의 값이 나온다.
*/

int solution(int n, vector<int> l, vector<int> r) {
	unordered_set<int> v(r.begin(), r.end());
	for (int i = 0; i < l.size(); i++) {
		if (v.find(l[i]) != v.end())
			v.erase(l[i]), l.erase(l.begin() + i--);
	}
	int a = n - l.size();
	sort(l.begin(), l.end());
	for (auto& t : l) {
		if (v.find(t - 1) != v.end())
			v.erase(t - 1), a++;
		else if (v.find(t + 1) != v.end())
			v.erase(t + 1), a++;
	}
	return a;
}