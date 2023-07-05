#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/implement-strstr/
문자열 찾기 방식은 다양하기에 경우에 따라 효율적인거 쓸 수 있도록.
*/

class Solution {
public:
    int strStr(string haystack, string needle) {       
		/*
		// 해시맵으로 단어 찾기 (197ms)
        if (needle.empty())
            return 0;
        unordered_map<string, int> a;
        string k = haystack.substr(0, needle.length());
        a[k] = 0;
        for (int i = 1; i + needle.length() <= haystack.length(); i++) {
            k.erase(k.begin()); k += haystack[i + needle.length() - 1];
            if (a.find(k) == a.end())
                a[k] = i;
        }
        return a.find(needle) == a.end() ? -1 : a[needle];
        */

        /*
		// stl 문자열 찾기 이용하기... 아마 완전탐색 기반으로 할 듯 (21ms)
		// 적은 단어수에서는 메모리 할당이 적기에 kmp보다 빠를듯?
        return haystack.find(needle);
        */

		// kmp 알고리즘 (3ms)
		// 예상대로 가장 빠름
		if (needle.empty())
			return 0;

		vector<size_t> lps, Result;
		lps.reserve(needle.length());
		lps.push_back(0);
		for (int i = 1, k = 0; i < needle.length(); i++) {
			while (k > 0 && needle[i] != needle[k])
				k = lps[k - 1];
			lps.push_back((needle[i] == needle[k] ? ++k : 0));
		}
		for (int i = 0, j = 0; i < haystack.length(); i++) {
			while (j > 0 && haystack[i] != needle[j])
				j = lps[j - 1];
			if (haystack[i] == needle[j]) {
				if (j == needle.length() - 1) {
					return i - needle.length() + 1;
					j = lps[j];
				}
				else j++;
			}
		}
		return -1;
    }
};