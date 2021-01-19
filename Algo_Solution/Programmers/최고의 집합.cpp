#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12938
여러 자연수의 곱이 가장 커질 때는 그 자연수들의 표준편차가 가장
작을 경우라는 것을 알아야 풀 수 있는 문제.
야간 수당과 같이 수학적인 배경이 있다면 풀기 쉽고 아니라면
머리를 굴려야 풀 수 있다....
난 수학이 잼병이라 머리를 굴려야했다.
이 문제를 통해 자연수 최대 곱에 대한 지식을 얻어간다.
*/

vector<int> solution(int n, int s) {
    vector<int> answer;
	if (n > s)
		return { -1 };
    int A = s / n, B = s % n;
	for (int i = 0; i < n; i++)
		answer.push_back(A);
	for (int i = answer.size() - 1, j = 0; j < B; i--, j++)
		answer[i]++;
    return answer;
}