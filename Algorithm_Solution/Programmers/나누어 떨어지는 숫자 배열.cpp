#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/12910
나누어 떨어지는 숫자 배열 문제.
난이도가 낮은 문제여서 람다 연습할겸 풀어봤다.
*/

vector<int> solution(vector<int> arr, int divisor) {
	return [&]()->vector<int> {
		set<int> p;
		for (auto& n : arr)
			if (!(n % divisor))
				p.insert(n);
		if (p.empty()) return { -1 };
		return vector<int>(p.begin(), p.end());
	}();
}