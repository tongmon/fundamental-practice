#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12945
피보나치 문제.
그냥 피보나치를 DP던 큐던 사용해서 구현하면 된다.
*/

int solution(int n) {
	queue<int> Q({ 1, 1 });
	for (int i = 2; i <= n; i++)
	{
		Q.push((Q.front() + Q.back()) % 1234567);
		Q.pop();
	}
	return Q.front();
}