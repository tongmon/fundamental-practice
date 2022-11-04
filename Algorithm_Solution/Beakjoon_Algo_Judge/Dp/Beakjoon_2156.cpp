#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2156
포도주가 담겨있는 잔을 선택하여 마셔 최대로 마실 수 있는 최대치를 구하는 문제이다.
이 경우도 Dp로 풀었다. 최대치 구하기, ~를 하는 가짓수를 구하는 문제는 Dp인지 의심을 해봐야한다.
Dp의 점화식을 세울 때는 n개 항부터 n-1인 경우, n-2인 경우... 따져가면서 세워보자
이 문제도 점화식 세울 때 귀찮게 만드는 점이 3잔 연속으로 못마시는 조건이였는데
이를 감안하여 세워보자. 잔을 쭉 고르다가 8번째 잔을 고를 때가 왔다 치자
이러면 Dp[8]은 7번째 잔을 고르고 6번째 잔을 고를 수 없으니 5번째 잔을 고르기까지 최대값인 dp[5]가 더해지는
Dp[8] = Drink[8] + Drink[7] + Dp[5]가 될 것이다... 하지만 이게 끝일까?
Dp[8] = Drink[8] + Dp[6] 이렇게 7을 건너뛰고 6번째 잔을 고르기까지 최대값을 더한 것도 될 수 있고,
Dp[8] = Dp[7] 완전히 8번째 잔을 고르지 않는 방법도 있을 것이다.
따라서 이 셋중에 가장 큰 값이 선정되어야 한다.
*/

int Drink[10001];
int Dp[10001];

int Dynamic(int Size)
{
    Dp[0] = Drink[0];
    if (Size > 1)
    {
        Dp[1] = Dp[0] + Drink[1];
        Dp[2] = max(Dp[1], max(Drink[0] + Drink[2], Drink[1] + Drink[2]));
        for (int i = 3; i < Size; i++)
        {
            Dp[i] = max(Dp[i - 1], max(Drink[i] + Drink[i - 1] + Dp[i - 3], Drink[i] + Dp[i - 2]));
        }
    }
    return Dp[Size - 1];
}

int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> Drink[i];
    }
    cout << Dynamic(N);
}