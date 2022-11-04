#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12944
평균 구하기 문제.
accumulate 함수 사용하면 쉽다.
*/

double solution(vector<int> arr) {
	return accumulate(arr.begin(), arr.end(), 0) / (double)arr.size();
}