#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/power-of-two/submissions/
해당되는 이진수 있나 없나 완전탐색으로 뒤적거리기
*/

class Solution {
public:
    bool isPowerOfTwo(int n) {
        long long k = 1, p = 0;
        do {
            if (n == k)
                return true;
            k *= 2;
        } while (++p < 31);
        return false;
    }
};