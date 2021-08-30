#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/77884
약수의 개수와 덧셈 문제.
하라는 데로 구현하면 된다.
*/

int Cnt(int n) {
	int k = 0;
	for (int i = 1; i <= n; i++)
		if (!(n % i)) k++;
	return k;
}

int solution(int left, int right) {
	int l, answer = 0;
	for (int i = left; i <= right; i++) {
		l = Cnt(i);
		answer += l % 2 ? -i : i;
	}
	return answer;
}