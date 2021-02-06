#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/longest-common-prefix/
가장 긴 접두사를 찾는 문제.
접두사이기에 맨 앞만 같은지 비교하면 문제가 풀린다.
이 문제로 구현 능력을 길러간다.
*/

class Solution {
public:
	string longestCommonPrefix(vector<string>& strs) {
		if (strs.empty())
			return "";
		string Prefix = strs[0];
		for (int i = 1; i < strs.size(); i++)
		{
			string A;
			for (int j = 0; j < strs[i].size() && j < Prefix.size(); j++) {
				if (strs[i][j] == Prefix[j])
					A.push_back(Prefix[j]);
				else
					break;
			}
			if (A.empty())
				return "";
			else
				Prefix = A;
		}
		return Prefix;
	}
};