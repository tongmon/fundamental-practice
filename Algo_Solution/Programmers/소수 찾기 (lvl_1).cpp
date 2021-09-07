#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12921
소수 찾기 문제.
에라토스테네스의 체 코드 기억 상기 시킬 겸 풀었다.
*/

int solution(int n) {
	int a = 0;
	vector<int> P(n + 1);
	P[0] = P[1] = 1;
	for (int i = 4; i <= n; i += 2) P[i] = 1;
	for (int i = 3; i <= sqrt(n); i+=2) {
		if (P[i]) continue;
		for (int j = i * i; j <= n; j += i)
			P[j] = 1;
	}
	for (auto& p : P)
		p ? a : ++a;
	return a;
}