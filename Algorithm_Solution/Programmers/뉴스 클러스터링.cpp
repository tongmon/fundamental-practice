#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/17677
뉴스 클러스터링 문제
해쉬맵 사용 능력을 보는 문제였다.
해쉬맵에 str1에서 추출한 녀석들, str2에서 추출한 녀석들의 개수를 pair로 묶어 저장한다.
pair에서 더 큰 수는 합집합을 작은 수는 교집합을 의미하게 된다.
합,교집합 다 구했으니 하란대로 답을 계산하면된다.
이 문제를 통해 구현속도를 늘려간다.
*/

unordered_map<string, pair<int, int>> Sets;

int solution(string str1, string str2) {
	int answer = 0, Inter = 0, Uni = 0;
	string Ary[2] = { str1, str2 };
	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < Ary[k].size() - 1; i++) {
			string A;
			A += toupper(Ary[k][i]);
			A += toupper(Ary[k][i + 1]);
			if ('A' <= A[0] && A[0] <= 'Z' && 'A' <= A[1] && A[1] <= 'Z') {
				if (Sets.find(A) == Sets.end())
					!k ? Sets[A].first = 1 : Sets[A].second = 1;
				else
					!k ? Sets[A].first++ : Sets[A].second++;
			}
		}
	}
	for (auto& S : Sets) {
		Uni += max(S.second.second, S.second.first);
		Inter += min(S.second.second, S.second.first);
	}
	if (!Uni) return 65536;
	answer = floor(65536 * float(Inter / (float)Uni));
	return answer;
}