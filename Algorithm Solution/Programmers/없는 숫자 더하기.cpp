#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/86051
그냥 구현문제라 람다 연습이나 했다. 
람다 끝에 () 붙이는거 잊지 마라.
*/

int solution(vector<int> numbers) {
	return [&]() -> int {
		int k = 0, A[10] = { 0, };
		for (auto& n : numbers)
			A[n] = 1;
		for (int i = 0; i < 10; i++)
			k += A[i] ? 0 : i;
		return k;
	}();
}