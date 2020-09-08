#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2110
이진탐색 문제이다.
처음에 어떻게 접근할지 막막했는데 이진탐색문제가 보통 답으로 제출되는 값이 탐색의 대상이 되는 것을 이용하여
두 집 사이의 공간 값의 최적을 이진 탐색하는 방향으로 코드를 짜니까 해결이 되었다.
주의해야 할 것은 집들의 값도 정렬을 해야한다는 것이다.
두 집 사이의 공간 값을 제일 작은 집부터 더해 가면서 가야 최적 공간 값을 구하기 원활하다.
정렬을 하지 않았다면 만약 차이 값이 3라고 하고 3개를 설치하는 상황에서 배열 상태가 1,8,2,9,4인 상태면
1 + 3보다 8이 크니까 8 선택 -> 8 - 2가 3보다 크니까 2선택 -> 2 + 3이 9보다 작으니 9선택이라는 불상사가 발생한다.
값이 정상적이면 1,4,9나 1,4,8이 나와야 하지만 위의 오답은 1,2,4,8,9 모두를 가리키게 된다.
이 문제를 통해 다른 이진탐색 문제처럼 어떤 특정 값을 찾는 방식이 아니라 최적의 값을 찾는 방식에도 이진탐색을 활용한다는 점을 상기했다.
그리고 문제마다 적절히 정렬을 사용할 수 있는 능력도 약간 길러졌다.
*/

#pragma warning(disable:4996)

int Cord[200001] = { 0, };

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    priority_queue<int, vector<int>, greater<int> > For_Sort;
    int N, C, Cordinate, Low = 1, High, Mid;
    unsigned int Wifi, Count = 1, Gap = 1;
    cin >> N >> C;
    for (int i = 0; i < N; i++)
    {
        cin >> Cordinate;
        For_Sort.push(Cordinate);
    }
    for (int i = 0; i < N; i++)
    {
        Cord[i] = For_Sort.top(); For_Sort.pop();
    }
    High = Cord[N - 1] - Cord[0];
    while (Low <= High)
    {
        Mid = (Low + High) / 2;
        Wifi = Cord[0];
        for (int i = 1; i < N && Count < C; i++)
        {
            if (Wifi + Mid <= Cord[i])
            {
                Count++; Wifi = Cord[i];
            }
        }
        if (Count == C)
        {
            Gap = Gap < Mid ? Mid : Gap;
            Low = Mid + 1;
        }
        else if (Count < C)
        {
            High = Mid - 1;
        }
        Count = 1;
    }
    cout << Gap;
}