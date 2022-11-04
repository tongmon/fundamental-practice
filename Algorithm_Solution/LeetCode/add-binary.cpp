#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/add-binary/
스트링 이진수를 덧셈하는 문제다.
이진수이기에 2로 나눈 몫과 나머지를 이용해 풀면된다.
덧셈이기에 기본적으로 올림수도 쓰여야된다.
이 문제를 통해 구현 속도를 늘려간다.
*/



class Solution {
public:
	string addBinary(string a, string b) {
		string Ans;
		int Up = 0;
		while (!a.empty() || !b.empty()) {
			int A = 0, B = 0, R;
			if (!a.empty())
				A = a.back() - '0';
			if (!b.empty())
				B = b.back() - '0';
			R = A + B + Up;
			Up = R / 2;
			Ans.push_back(R % 2 + '0');
			if (!b.empty())
				b.pop_back();
			if (!a.empty())
				a.pop_back();
		}
		if (Up)
			Ans.push_back('1');
		reverse(Ans.begin(), Ans.end());
		return Ans;
	}
};