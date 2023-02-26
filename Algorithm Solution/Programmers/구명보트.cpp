#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/42885
*/

int Peo[241];

int solution(vector<int> people, int limit) {
	int answer = 0;
	for (int i = 0; i < people.size(); i++)
	{
		Peo[people[i]]++;
	}
	sort(people.begin(), people.end());
	while (!people.empty()) {
		if (Peo[people.back()] > 0) {
			int W = limit - people.back();
			for (int j = 40; j <= W; j++) {
				if (Peo[j] > 0) {
					Peo[j]--; break;
				}
			}
			Peo[people.back()]--; answer++;
		}
		people.pop_back();
	}
	return answer;
}