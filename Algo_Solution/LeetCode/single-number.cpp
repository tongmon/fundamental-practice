#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/single-number/
그냥 무지성으로 공간을 사용해서 푼다면 쉽게 느껴지는 문제지만
좀 만 더 생각해보면 공간과 시간을 모두 아낄 수 있는 무친 최적화가 가능한 문제다...
*/

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        /*
        // 그냥 맵을 사용해서 푸는 방식...
        // O(n)이 두 번 진행된다.
        unordered_map<int, int> m;
        for (const auto& n : nums)
            m[n]++;
        int r = -1;
        for (const auto& n : m)
            if (n.second == 1) {
                r = n.first; 
                break;
            }
        return r;
        */

        // 무친 방법... 어떻게 요런 생각을 했지?
        // xor 연산의 특징을 이용한다.
        // 문제에서는 단 한개의 수를 제외하고 나머지 수는 짝수번 등장한다는 조건이 있었다.
        // 특정 수를 짝수번 xor연산을 하면 결국엔 0이 도출된다. 1^1=0, 0^0=0이니 말이다.
        // 그렇다면 특정 수 짝수번 xor연산 중간에, 아니면 아무런 위치에 수를 끼워넣는다면?
        // 특정 수가 도출될 것이다.
        // 예시를 보면 13 ^ 93 ^ 13 = 93이다.
        // 이러한 원리로 한번의 O(n) 연산을 통해 답이 도출 가능하다.
        int b = 0;
        for (const auto& n : nums)
            b ^= n;
        return b;
    }
};