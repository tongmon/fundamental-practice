#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/68935
3진법 뒤집기 문제.
하라는 데로 구현하면 된다.
*/

int solution(int n) {
	int answer = 0, k = 1;
	string T;
	while (n) {
		T += to_string(n % 3);
		n /= 3;
	}
	for (int i = T.size() - 1; i >= 0; i--) {
		answer += k * (T[i] - '0');
		k *= 3;
	}
	return answer;
}