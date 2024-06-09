#include <iostream>
#include <map>
using namespace std;

/*
https://leetcode.com/problems/roman-to-integer/
로마수를 10진수로 바꾸면 된다.
앞에 숫자가 뒤 숫자보다 무조건 커야하지만 IV와 같은 앞의 숫자가 더 작은 예외가 있기에 따져주면 된다.
*/

class Solution {
public:
	int romanToInt(string s) {
		int a = 0;
		map<char, int> r{ {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000} };
		for (int i = 0; i < s.size(); i++)
		{
			if (i + 1 < s.size() && ((s[i] == 'I' && (s[i + 1] == 'V' || s[i + 1] == 'X')) ||
				(s[i] == 'X' && (s[i + 1] == 'L' || s[i + 1] == 'C')) ||
				(s[i] == 'C' && (s[i + 1] == 'D' || s[i + 1] == 'M'))))
			{
				a += r[s[i + 1]] - r[s[i++]];
				continue;
			}
			a += r[s[i]];
		}
		return a;
	}
};