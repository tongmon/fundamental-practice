#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12914
멀리뛰기 문제.
1칸 2칸 이렇게 뛸 수 있고 개수를 구해야하고 값이 커지니
1234567로 나눈 나머지를 구해야한다....
Dp냄새가 너무 강하게 난다. 게다가 1칸 2칸이면 피보니치일
확률 또한 높다.
3칸을 가는 경우를 보면 맨 앞쪽을 생각하면 된다.
맨 앞쪽이 1칸으로 고정되는 경우 --> (어떤 경우 2칸) + 1칸
맨 앞쪽이 2칸으로 고정되는 경우 --> (어떤 경우 1칸) + 2칸
2칸을 만드는 경우는 1+1, 2 / 1칸을 만드는 경우 1가지
4칸을 만드는 경우도 같은 원리다 Dp[3] + Dp[2] = Dp[4]
결국 Dp[n-1] + Dp[n-2] = Dp[n]... 피보나치
이 문제를 통해 Dp를 상기시키고 간다.
*/

long long solution(int n) {
	using ll = long long;
	ll answer = 0;
	queue<ll> Q({ 1,1 });
	for (int i = 2; i <= n; i++)
	{
		Q.push((Q.front() + Q.back()) % 1234567);
		Q.pop();
	}
	answer = Q.back();
	return answer;
}