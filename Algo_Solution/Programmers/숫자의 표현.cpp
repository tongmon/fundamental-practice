#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12924
숫자의 표현
자연수인데 연속이라 바로 투 포인터가 떠올라 그리 구현했다.
투 포인터 문제라는 것 외엔 따로 설명할 것이 없다.
투 포인터는 예전에도 꽤 접해봐서 그런지 바로 떠오르더라.
*/

int solution(int n) {
	int answer = 0;
	int Sum = 1, St = 1, End = 1;
	while (End <= n && St <= n) {
		if (Sum < n) {
			End++;
			Sum += End;
		}
		else if (Sum > n) {
			Sum -= St;
			St++;
		}
		else {
			answer++;
			Sum -= St;
			St++;
		}
	}
	return answer;
}