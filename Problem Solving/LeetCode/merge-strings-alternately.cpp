#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/merge-strings-alternately/
문자열 번갈아가며 추가
*/

class Solution
{
public:
    string mergeAlternately(string word1, string word2)
    {
        string r;
        for (int i = 0, j = 0, k = 0; i < word1.size() + word2.size(); i++)
            if (i % 2)
                if (word2.size() > k)
                    r += word2[k++];
                else
                    r += word1[j++];
            else
                if (word1.size() > j)
                    r += word1[j++];
                else
                    r += word2[k++];
        return r;
    }
};