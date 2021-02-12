#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/plus-one/submissions/
주어진 수열에 1을 더하면 어떤 수가 되는지 알아내는 문제.
자릿수가 100이 최대이기에 일반적인 숫자 자료형으로 담기지도 않는다.
따라서 덧셈의 올림수를 이용해서 풀어야 한다.
다음 올림수는 십진수이기에 A / 10, 해당 자리의 수 A % 10
유의점은 마지막에 올림수가 0이 아니면 그것도 자릿수이기에
정답 배열에 넣어주어야 한다.
*/

class Solution {
public:
	vector<int> plusOne(vector<int>& digits) {
		vector<int> Ans;
		int Up = 1;
		while (!digits.empty()) {
			int A = digits.back() + Up;
			Up = A / 10;
			Ans.push_back(A % 10);
			digits.pop_back();
		}
		if (Up)
			Ans.push_back(Up);
		reverse(Ans.begin(), Ans.end());
		return Ans;
	}
};