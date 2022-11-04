#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12928
약수의 합 문제.
약수의 합이여서 1부터 n까지 나눠본다.
*/

int solution(int n) {
	int k = 0;
	for (int i = 1; i <= n; i++)
		k += n % i ? 0 : i;
	return k;
}