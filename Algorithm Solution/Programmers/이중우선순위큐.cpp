#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/42628
이중우선순위큐 문제다.
백준에서 풀 때는 힙 두개와 해쉬맵을 사용하여 풀었던 것으로 기억하는데
요번에 풀 때는 그냥 멀티셋이 생각나서 멀티셋을 때려박아 풀었다.
굉장히 편하게 문제가 풀렸다.
멀티셋이 좋은 점이 삽입, 삭제가 logN에 이루어지고 항상 정렬이 유지된다.
이 문제를 통해 구현속도를 늘려간다.
*/

vector<int> solution(vector<string> operations) {
	vector<int> answer;
	multiset<int> Q;
	for (auto& A : operations) {
		if (A[0] == 'I') {
			int N = stoi(A.substr(2, A.size() - 1));
			Q.insert(N);
		}
		else if (!Q.empty()) {
			if (A[2] == '1') { 
				auto iter = Q.end();
				iter--;
				Q.erase(iter);
			}
			else Q.erase(Q.begin());
		}
	}
	if (Q.empty())
		return { 0,0 };
	auto iter = Q.end();
	iter--;
	return { *iter , *(Q.begin()) };
}