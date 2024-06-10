/*
https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/
슬라이딩 윈도우 문제다.
앞에 모음이 빠지는 것과 새로 들어오는 글자가 모음인 경우를 따져주면 된다.
*/

class Solution
{
public:
    int maxVowels(string s, int k)
    {
        int r = 0, t = 0;
        for (int i = 0; i < k; i++)
            if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u')
                t++;
        r = t;
        for (int i = 1; i < s.size() - k + 1; i++)
        {
            if (s[i - 1] == 'a' || s[i - 1] == 'e' || s[i - 1] == 'i' || s[i - 1] == 'o' || s[i - 1] == 'u')
                t--;
            if (s[i + k - 1] == 'a' || s[i + k - 1] == 'e' || s[i + k - 1] == 'i' || s[i + k - 1] == 'o' || s[i + k - 1] == 'u')
                t++;
            r = max(r, t);
        }
        return r;
    }
};