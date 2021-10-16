#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/87389
나머지가 1이 되는 수 찾기 문제.
완전 탐색하면 된다.
*/

int solution(int n) {
	for (int i = 1; i < n; i++)
		if (n % i == 1) return i;
}