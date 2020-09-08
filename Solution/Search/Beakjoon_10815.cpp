#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/10815
기본적인 이진탐색문제....
그냥 이진탐색을 때려박으면 된다.
*/

#pragma warning(disable:4996)

int Card_N = 0;
vector<int> Cards, Result;

int is_Card(int N)
{
    int Low = 0, High = Card_N - 1, Mid;
    while (Low <= High)
    {
        Mid = (Low + High) / 2;
        if (Cards[Mid] < N)
        {
            Low = Mid + 1;
        }
        else if (Cards[Mid] > N)
        {
            High = Mid - 1;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int Number, is_Card_N;
    cin >> Card_N;
    for (int i = 0; i < Card_N; i++)
    {
        cin >> Number;
        Cards.push_back(Number);
    }
    sort(Cards.begin(), Cards.end());
    cin >> is_Card_N;
    for (int i = 0; i < is_Card_N; i++)
    {
        cin >> Number;
        Result.push_back(is_Card(Number));
    }
    for (int i = 0; i < is_Card_N; i++)
    {
        cout << Result[i] << " ";
    }
}