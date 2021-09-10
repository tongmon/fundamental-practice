#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12906
같은 숫자는 싫어 문제.
예전 숫자를 체크해주면 된다.
*/

vector<int> solution(vector<int> arr)
{
	vector<int> a;
	int b = 10;
	for (auto& n : arr) {
		if (b != n) {
			b = n;
			a.push_back(b);
		}
	}
	return a;
}