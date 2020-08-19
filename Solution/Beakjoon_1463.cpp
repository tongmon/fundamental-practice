#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1463
기본적인 DP문제
문제를 분할하여 푼다는 사실은 합병정렬과 같은 분할정복과 같으나
분할정복은 문제를 분할하여 풀때 중복되는 문제가 없으나 DP는 있다는 것이 차이점이다.
고로 Dp는 앵간하면 밑과 같은 값 결과 저장소가 따로 필요하다.
DP저장소의 인덱스가 1000001인 이유는
인풋값이 1000000까지 들어오고 이에 따라 배열 인덱스가 연관되어 분할한 문제들의 값이 저장되기 때문이다.
밑 문제는 Dp 대신 BFS로 작성되어있다. 따라서 제일 먼저 1이 되는 녀석의 카운터 값이 답이 된다.
*/

int Dp[1000001] = { 0, };

void Compare(int a, int b)
{
    if (Dp[a] == 0)
    {
        Dp[a] = Dp[b] + 1;
    }
    else if (Dp[a] != 0)
    {
        Dp[a] = min(Dp[a], (Dp[b] + 1));
    }
}

void Div(int X)
{
    if (X == 1)
    {
        Dp[1] = 0; return;
    }
    queue<int> Num;
    if (X % 3 == 0)
    {
        Dp[X / 3] = Dp[X] + 1;
        Num.push(X / 3);
    }
    if (X % 2 == 0)
    {
        Dp[X / 2] = Dp[X] + 1;
        Num.push(X / 2);
    }
    if (X % 3 != 0 || X % 2 != 0)
    {
        Dp[X - 1] = Dp[X] + 1;
        Num.push(X - 1);
    }

    while (Num.empty() == false)
    {
        int buffer = Num.front();
        Num.pop();
        if (buffer == 1)
        {
            return;
        }
        if (buffer % 3 == 0)
        {
            Compare(buffer / 3, buffer);
            Num.push(buffer / 3);
        }
        if (buffer % 2 == 0)
        {
            Compare(buffer / 2, buffer);
            Num.push(buffer / 2);
        }
        if (buffer % 3 != 0 || buffer % 2 != 0)
        {
            Compare(buffer - 1, buffer);
            Num.push(buffer - 1);
        }
    }
}

int main()
{
    int X;
    scanf("%d", &X); Div(X);
    cout << Dp[1];
}