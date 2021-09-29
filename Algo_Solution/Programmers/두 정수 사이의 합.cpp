#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12912
두 정수 사이의 합 문제.
람다 연습이다.
*/

using ll = long long;

ll solution(int a, int b) {
	return [&]() {ll s = 0; b < a ? swap(a, b) : void(); for (int i = a; i <= b; i++) s += i; return s; }();
}