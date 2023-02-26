#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1654
기본적인 이분탐색 문제다...
이분탐색을 엉성하게 알고 있어서 그런지 제출시에 많이 틀렸다.
그리고 mid가 0이 나오는 경우에 대한 예외처리도 안해줘서 더 많이 틀렸다....
항상 기억하자!
이분 탐색을 하려면 재귀로 하던 반복으로 하던 Low, Mid, High가 필요하고
찾으려는 원소가 나오지 않을 때에는 Low는 Mid + 1, High는 Mid - 1로 변한다. 
그리고 다시 Mid는 (Low + High) / 2가 된다. 이것만 기억하고 응용하자.
문제적인 관점에서 볼 때 이 문제를 풀면서 이진탐색이 알고리즘 문제에서 어떻게 쓰이는지 약간의 감을 잡았다.
이진탐색은 탐색하여 특정 값을 찾아내는 역할도 있지만 특정 값을 찾지 않고 최적의 값을 찾는 경우에도 쓰인다는 것을 깨달았다.
이 문제도 보면 이진 탐색을 while문이 빠져나가기 전까지 계속 돌려 최적의 값을 찾아낸다. 
특정 값이 정해져있는 문제가 아니기 때문이다.
*/

#pragma warning(disable:4996)

long long K = 0, N = 0;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    vector<int> Storage; 
    long long Sum = 0;
    cin >> K >> N;
    unsigned int Len, Count = 0;
    for (int i = 0; i < K; i++)
    {
        cin >> Len; Sum = Sum + Len;
        Storage.push_back(Len);
    }
    long long Low = 0, High = Sum / N, Standard, Bigone = 1;
    while (Low <= High)
    {
        Standard = (Low + High) / 2;
        if (Standard == 0)
        {
            break;
        }
        for (int i = 0; i < Storage.size(); i++)
        {
            Count = Count + (Storage[i] / Standard);
        }
        if (Count >= N)
        {
            Bigone = Bigone < Standard ? Standard : Bigone;
            Low = Standard + 1;
        }
        else if (Count < N)
        {
            High = Standard - 1;
        }
        Count = 0;
    }
    cout << Bigone;
}