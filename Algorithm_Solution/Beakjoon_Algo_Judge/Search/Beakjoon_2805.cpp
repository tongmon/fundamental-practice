#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2805
이진 탐색 문제다.
이 문제도 역시 이진탐색을 어떤 배열 값을 찾으려고 쓰기 보다는 최적의 값을 찾기 위해 쓴다.
이 문제에서 주의 할 점은 나무의 높이가 0미터가 될 수도 있다는 점이다.
*/

#pragma warning(disable:4996)

int Tree[1000001] = { 0, };

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int N;
    long long M, Meter, H, Sum = 0, Low = 0, High = 0, Highest = 0;
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        cin >> Meter;
        Tree[i] = Meter;
        if (Meter > High)
        {
            High = Meter;
        }
    }
    while (Low <= High)
    {
        H = (Low + High) / 2;
        for (int i = 0; i < N; i++)
        {
            if (H < Tree[i])
            {
                Sum = Sum + Tree[i] - H;
            }
        }
        if (Sum >= M)
        {
            Highest = Highest < H ? H : Highest;
            Low = H + 1;
        }
        else if (Sum < M)
        {
            High = H - 1;
        }
        Sum = 0;
    }
    cout << Highest;
}