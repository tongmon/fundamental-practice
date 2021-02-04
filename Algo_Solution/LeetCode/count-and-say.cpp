#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/count-and-say/
구현 능력 테스팅하는 문제다.
반복문 돌리면서 문제에서 하라는 데로 하면 된다.
1 --> 1이 한개 11 --> 1이 두개 21 --> 2가 한개 1이 한개 1211....
이러한 규칙으로 진행하면 된다.
이 문제를 통해 구현력을 길러간다.
*/

class Solution {
public:
	string countAndSay(int n) {
		string Ans = "1";
		for (int i = 1; i < n; i++)
		{
			string Buf;
			char back = Ans[0];
			int Cnt = 0;
			for (auto str : Ans) {
				if (back == str)
					Cnt++;
				else {
					Buf += to_string(Cnt);
					Buf.push_back(back);
					Cnt = 1;
					back = str;
				}
			}
			Buf += to_string(Cnt);
			Buf.push_back(back);
			Ans = Buf;
		}
		return Ans;
	}
};