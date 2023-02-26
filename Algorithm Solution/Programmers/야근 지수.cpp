#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12927
제곱수의 합을 최소로 만드는 것을 따지는 문제인데
제곱수의 합이 최소이게 하기 위해서는 제곱수들 중 빼는 녀석을 고를 때
현재 가장 큰 녀석, 그니깐 예를 들면 7, 4, 5 이 수들의 제곱합을 따질 경우
1을 저 3개 수 중 어떤 것에서 빼야하냐면 7이 제일 크니까 7에서 빼면된다는 말이다.
그래서 현 상태에서 제일 큰 녀석을 알 수 있는 우선순위 큐를 이용하여 계속 빼준다.
빼줄거 다 뺏으면 제곱합의 결과를 구하고 그게 답이 된다.
다른 사람들 풀이를 봐도 다 거기서 거기더라
*/

long long solution(int n, vector<int> works) {
	long long answer = 0;
	priority_queue<int> Q;
	for (auto A : works) {
		Q.push(A);
	}
	while (n > 0) {
		int Top = Q.top(); 
		if (!Top) return answer;
		Q.pop();
		Top -= 1; n -= 1;
		Q.push(Top);
	}
	while (!Q.empty()) {
		int Top = Q.top();
		answer += Top * Top;
		Q.pop();
	}
	return answer;
}