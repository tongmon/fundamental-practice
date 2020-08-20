#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/11726
타일링 문제다...
Dp를 이용한 점화식 문제인데 이 문제의 점화식이 피보나치와 똑같은 것을 알 수 있다.
이 문제를 통해 Dp문제 같다 싶으면 점화식을 따져보는 습관을 길러야겠다고 생각했다...
처음에 점화식 따지지도 않고 막가파로 "1과 2의 조합 경우의 수구나!" 하고 재귀 존나 돌렸더니 시간초과만 존나 떳다.
*/

int Fib(int N)
{
    queue<int> Fibo; int counter = 0;
    Fibo.push(0); Fibo.push(1);
    while (counter != N)
    {
        int one = Fibo.front();
        if (one > 10007)
        {
            one = one % 10007;
        }
        int two = Fibo.back();
        if (two > 10007)
        {
            two = two % 10007;
        }
        Fibo.push(one + two);
        Fibo.pop(); counter++;
    }
    return Fibo.back();
}

int main()
{
    int N;
    cin >> N;
    cout << Fib(N) % 10007;
}