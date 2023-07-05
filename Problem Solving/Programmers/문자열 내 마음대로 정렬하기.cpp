#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12915
문자열 내 마음대로 정렬하기 문제.
전역변수를 사용하면 깔끔하게 풀 수 있다.
*/

int N;

bool Cmp(string &A, string &B) {
	if (A[N] == B[N])
		return A < B;
	return A[N] < B[N];
}

vector<string> solution(vector<string> strings, int n) {
	N = n;
	sort(strings.begin(), strings.end(), Cmp);
	return strings;
}