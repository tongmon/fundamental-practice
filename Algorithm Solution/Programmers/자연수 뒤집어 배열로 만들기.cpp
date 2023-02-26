#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12932
자연수 뒤집어 배열로 만들기 문제.
람다 연습할 겸 풀어봤다.
*/

vector<int> solution(long long n) {
	string a = to_string(n);
	transform(a.begin(), a.end(), a.begin(), [](char& c) { return c - '0'; });
	return vector<int>(a.rbegin(), a.rend());
}