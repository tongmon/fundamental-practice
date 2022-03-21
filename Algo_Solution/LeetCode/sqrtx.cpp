#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/sqrtx/
0에서 주어진 x까지 이진 탐색으로 빠르게 찾아가는 방식을 구현할 수도 있고
그냥 나 처럼 기존 함수들을 사용해도 된다...
속도는 이진탐색 방식과 내가 한 방식이 모두 0ms가 나왔다.
*/

class Solution {
public:
    int mySqrt(int x) {
        return floor(sqrt(x));

        /*
        // 이진탐색...
        int low = 0, high = x, ans = 0;
        while (low <= high) {
            long long mid = (low + high) / 2;
            if (mid * mid <= x) {
                ans = mid;
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        return ans;
        */
    }
};