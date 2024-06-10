/*
https://leetcode.com/problems/determine-if-two-strings-are-close/
문제만 두가지 연산을 무한대로 사용해서 word1을 word2로 만들 수 있으면 된다고 되어 있는데...
이것만 보면 헷갈리고 본질을 봐야 한다.
1. 글자 유형이 모두 같아야 한다.
2. 글자 개수 양상이 같아야 한다. (ex. word1 (2, 5, 3, 5) / word2 (5, 2, 3, 5) 면 양상이 같은 것)
위 두개의 조건이 충족되면 두 글자는 연산으로 같아질 수 있다.
*/

class Solution
{
public:
    bool closeStrings(string word1, string word2)
    {
        multiset<int> n[2];
        set<char> v[2];
        map<char, int> m[2];
        for (int i = 0; i < 2; i++)
        {
            string* p = i % 2 ? &word2 : &word1;
            for (const auto& c : *p)
            {
                if (m[i].find(c) == m[i].end())
                    m[i][c] = 0;
                m[i][c]++;
            }
        }
        for (int i = 0; i < 2; i++)
            for (const auto& d : m[i])
            {
                n[i].insert(d.second);
                v[i].insert(d.first);
            }
        return n[0] == n[1] && v[0] == v[1];
    }
};
