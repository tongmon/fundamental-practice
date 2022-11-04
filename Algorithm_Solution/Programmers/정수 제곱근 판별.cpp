#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12934
정수 제곱근 판별 문제.
그냥 구현 문제.
*/

using ll = long long;

ll solution(ll n) {
	ll p = sqrtl(n);
	return p * p == n ? ++p * p : -1;
}