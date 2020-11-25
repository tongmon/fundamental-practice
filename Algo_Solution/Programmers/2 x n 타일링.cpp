#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12900
전형적인 피보나치 DP문제... 백준에서 이미 풀어본 문제 복습할 겸 푼거라
별 설명을 적진 않겠다.
*/

int solution(int n) {
	int answer = 0;
	queue<long long> Q({ 1,1 });
	while (n > 0) {
		long long K = (Q.front() + Q.back()) % 1000000007;
		Q.pop(); Q.push(K); n--;
	}
	answer = Q.front();
	return answer;
}