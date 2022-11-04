#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/valid-parentheses/
스택을 이용한 괄호 검사 문제...
같은 문제 많이 풀어봤으니 기억 상기하자.
특이한 점은 for문을 도는 경우 속도인데
for (auto& c : s) -> 3ms
for (auto c : s) -> 0ms
for (const auto& c : s) -> 7ms
위와 같이 나왔다!
그냥 참조 안한 순회가 가장 빠르다니...
*/

class Solution {
public:
    bool isValid(string s) {
        stack<int> a;
        for (auto& c : s) {
            if (c == '(' || c == '[' || c == '{')
                a.push(c);
            else if (!a.empty() && (a.top() == c - 2 || a.top() == c - 1))
                a.pop();
            else
                return 0;
        }
        return a.empty();
    }
};