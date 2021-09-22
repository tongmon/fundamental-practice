#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/68936
쿼드압축 후 개수 세기 문제.
재귀 형식으로 접근하면 된다.
4개 모이면 1로 만들고 이를 반복하면 된다.
*/

using V = vector<int>;
vector<V> A;

V func(int x, int y, int s) {
	V r = { 0,0 }, t;
	if (s == 1)
		return { !A[y][x], A[y][x] };
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++) {
			t = func(x + j * s / 2, y + i * s / 2, s / 2);
			r[0] += t[0], r[1] += t[1];
		}
	return { !r[1] ? 1 : r[0], !r[0] ? 1 : r[1] };
}

V solution(vector<V> arr) {
	A = arr;
	return func(0, 0, A.size());
}