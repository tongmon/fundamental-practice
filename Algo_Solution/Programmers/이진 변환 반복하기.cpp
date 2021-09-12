#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/70129
이진 변환 반복하기 문제.
문제에서 주어진 그대로 이진변환을 반복하면 된다.
*/

vector<int> solution(string s) {
	string S[2];
	int z = 0, n = 0, l; S[0] = s;
	while (S[0] != "1") {
		for (auto& c : S[0])
			if (c == '1')
				S[1] += c;
			else z++;
		l = S[1].size(), S[0].clear(), S[1].clear();
		while (l) {
			S[0] += (l % 2 + '0');
			l /= 2;
		}
		reverse(S[0].begin(), S[0].end());
		n++;
	}
	return { n,z };
}