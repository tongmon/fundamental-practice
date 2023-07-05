/*
https://leetcode.com/problems/reverse-integer/
실수하기 너무 좋은 문제....
인트형 최대 최소 범위를 정확히 인지하고 있어야 풀리는 문제이다.
음수 절댓값이 양수 절댓값보다 하나 더 크다는 것까지 알고 있어야된다....
long long으로 선언해서 int 형 자료 범위에 들어가지 않으면 0을 출력해야 한다.
long long으로 선언하는 이유는 변환한 값이 겁나 커지는 경우가 있고
아까 말했듯이 정수형 음수 최솟값이 양수 최솟값보다 하나 크기에 음수를 양수로 변환하는 순간
이상한 값이 ans로 들어가게 된다.
자료형의 최대, 최솟값을 도출해주는 numeric_limits<자료형>도 알아가자!
<limits> 헤더에 포함된다.
*/

class Solution {
public:
    int reverse(int x) {
        bool minus = 0;
        long long ans = 0, mult = 1, nx = x;
        if (nx < 0) {
            nx = -nx; minus = 1;
        }
        string A = to_string(nx);
        for (auto str : A) {
            ans += (str - '0') * mult;
            mult *= 10;
        }
        ans = minus ? -ans : ans;
        if (numeric_limits<int>::min() <= ans && ans <= numeric_limits<int>::max())
            return ans;
        return 0;
    }
};