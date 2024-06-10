#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/reverse-words-in-a-string/
문자열에서 단어 역순 뒤집어서 반환하기
*/

class Solution
{
public:
    string reverseWords(string s)
    {
        string r, w;
        std::vector<string> ss;
        for(const auto& l : s)
        {
            if (l != ' ')
                w += l;
            else if (!w.empty())
            {
                ss.push_back(std::move(w));
                w = "";
            }
        }
        if (!w.empty())
            ss.push_back(std::move(w));
        for (int i = ss.size() - 1; i >= 0; i--)
            r += (ss[i] + " ");
        r.pop_back();
        return r;
    }
};