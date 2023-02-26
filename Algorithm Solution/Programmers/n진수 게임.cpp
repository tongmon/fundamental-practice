#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/17687
n진수 게임 문제.
진법 변환만 잘하면 되는 문제다.
100명의 사람 게임을 하는데 1000번의 순서가 돌아온다면
그 100명 안에서 어느 순서던지 일단 맘편하게 100 * 1000을 해서 결과를 구하는게
편해서 그렇게 구현했다.
그리고 그 문자열에서 자신에 순서에 알맞은 단어를 고를 때는 나머지 연산을 사용하면 된다.
인덱스가 0부터 시작이니 +1을 마지막에 해주면 되고...
이 문제를 통해 구현 속도를 늘려간다.
*/

string Nums(int n, int Number) {
	string A;
	int buf;
	while (Number > 0) {
		buf = Number % n;
		if (buf >= 10)
			A.push_back('A' + buf - 10);
		else
			A.push_back('0' + buf);
		Number /= n;
	}
	reverse(A.begin(), A.end());
	return A;
}

string solution(int n, int t, int m, int p) {
	string answer = "0", sol;
	int N = 1;
	while (answer.size() < t * m) {
		answer += Nums(n, N);
		N++;
	}
	for (int i = 0; i < answer.size() && t > 0; i++) {
		if (i % m + 1 == p) {
			t--;
			sol.push_back(answer[i]);
		}
	}
	return sol;
}