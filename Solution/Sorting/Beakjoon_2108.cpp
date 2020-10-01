#include <iostream>
#include <unordered_map>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2108
개또라이 욕나오는 문제.
로직짜기 개쉬운데 진짜.... 하......
로직을 짜고 소수점 반올림에 대한 지식이 부족해서 푸는데 오래걸렸다...
이 문제에서 배운 굉장히 중요한 것은 (double)a / b의 값하고 (double)(a / b) 값하고 다르다는 것이다....
(double)a / b 가 실제 원하는 값이 나오고 (double)(a / b) 얘는 a / b에서 소수가 짤린 다음 실수 변환이 진행된다.
이것 땜시 겁나 시간 버렸다. 도대체 진짜.... 그나마 알아냈으니 다행이다.
그리고 정밀도를 위해서 float대신에 double을 애용하자!
그리고 반올림 함수 round 기억하자 아니면 내림함수 floor(a + 0.5)로 반올림 함수로 만들수 있다.
*/

#pragma warning(disable:4996)

int Plus_Ary[4001], Minus_Ary[4001], Ary[500001];
long long Sum = 0;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int N, buffer, MAX = -1;
    vector<int> Freq_sto;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> Ary[i];
        Sum = Sum + Ary[i];
        if (Ary[i] >= 0)
        {
            Plus_Ary[Ary[i]] = Plus_Ary[Ary[i]] + 1; buffer = Plus_Ary[Ary[i]];
        }
        else
        {
            Minus_Ary[-Ary[i]] = Minus_Ary[-Ary[i]] + 1; buffer = Minus_Ary[-Ary[i]];
        }
        if (buffer > MAX) MAX = buffer;
    }
    sort(Ary, Ary + N);
    for (int i = 4000; i > 0; i--)
    {
        if (MAX == Minus_Ary[i]) Freq_sto.push_back(-i);
    }
    for (int i = 0; i <= 4000; i++)
    {
        if (MAX == Plus_Ary[i]) Freq_sto.push_back(i);
    }
    cout << round((double)Sum / N) << '\n' << Ary[N / 2] << '\n';
    if (Freq_sto.size() == 1) cout << Freq_sto.front() << '\n';
    else cout << Freq_sto[1] << '\n';
    cout << Ary[N - 1] - Ary[0];
}