#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/11047
그리디 문제이다.
그리디 문제를 풀 때는 DP문제와 혼동이 생기기 쉬우니 잘 생각해서 풀어야 한다.
최선의 선택을 매 순간마다 고르게 코드를 짜면 쉽게 풀린다.
코드의 효율이 갈릴 수 있는 부분이 있는데 이중for문으로 동전의 값을 그냥 빼가면서 카운팅을 할 수도 있다.
효울이 굉장히 떨어진다. 
N * N 연산이다. 32ms나 걸렸다.
다른 방법으로 어짜피 그 동전의 가격을 뺄 수 있으면 K / 동전가치를 한 값이 카운팅 되면 되는 것 아닌가?
그리고 떨거지 K % 동전가치 값을 다시 검사해가면 되는 것 아닌가?
굉장히 효율적이다. 
N번 연산으로 끝난다 0ms가 걸렸다.
*/

#pragma warning(disable:4996)

int Ary[10];

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int N, K, count = 0; cin >> N >> K;
    for (int i = 0; i < N; i++)
    {
        cin >> Ary[i];
    }
    for (int i = N - 1; i >= 0 && K > 0; i--)
    {
        if (Ary[i] <= K) // 효율이 굉장히 상승한다. 
        {
            count = count + K / Ary[i];
            K = K % Ary[i];
        }
        /*
        // 직관적이긴 하지만 효율이 떨어지는 방식
        while (Ary[i] <= K)
        {
            K = K - Ary[i]; count++;
        }
        */
    }
    cout << count;
}