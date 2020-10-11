#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1806
투 포인터 문제다.
일단 배열의 입력이 모두 자연수여서 약간 의심이 들었고 문제가 부분합이라 투 포인터로 확정지을 수 있었다.
그냥 투 포인터 알고리즘 쓰고 합을 만족하면서 그 구간 중에 제일 작은 녀석을 구하면 된다.
이 문제를 통해 투 포인터 알고리즘 문제에 대한 감을 더 키워간다.
*/

int N, S, Len = 200000;
short Ary[100001];

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> N >> S;
    for (int i = 0; i < N; i++)
    {
        cin >> Ary[i];
    }
    int Low = 0, High = 0, Sum = 0;
    while (High < N || Sum >= S)
    {
        if (Sum >= S)
        {
            Sum = Sum - Ary[Low++];
            Len = min(Len, High - Low + 1);
        }
        else if (High < N) Sum = Sum + Ary[High++];
    }
    if (Len == 200000) cout << 0;
    else cout << Len;
}