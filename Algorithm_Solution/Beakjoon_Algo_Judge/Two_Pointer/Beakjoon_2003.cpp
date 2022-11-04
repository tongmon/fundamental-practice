#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2003
투 포인터라는 알고리즘으로 접근하는 문제다.
투 포인터는 연속적인 부분합을 구하는 경우 사용되는 알고리즘인데 처음에 두 포인터는 처음 배열 원소를 가리킨다.
현재 처음 포인터에서 마지막 포인터까지의 부분합이 작다면 더 크게 만들어 주어야하기에 마지막 포인터 부분을 증가시켜 다음 원소를 더해준다.
이때 알 수 있는 것은 투 포인터는 모든 배열 원소가 자연수라는 것을 가정한다는 것이다. 마지막 포인터를 증가시켜주는 이유가 부분합을 더 크게 만든다는
가정을 하고 있는 알고리즘이기 때문이다.
아무튼 그래서... 만약에 반대로 부분합이 목표치보다 더 커진다면? 처음 포인터를 반대로 증가시키고 부분합은 감소된다.
이를 언제까지 반복해야 하냐면 마지막 포인터가 배열의 마지막까지 다 가리켰는데 현재 부분합이 목표치보다 작다? 그러면 그만하면 된다.
왜냐면 부분합은 마지막 포인터가 모든 배열을 다 가리키고 이제 더 가리킬게 없기 때문에 줄어들일 밖에 안남았기 때문이다. (처음 포인터가 증가하며)
이러한 알고리즘을 사용하면 시간복잡도 단! N만에 문제가 풀린다.
간단하게 생각가능한 이중for문보다 굉장히 빨라진다!
요약하자면 모든 원소가 자연수고 부분합을 구해야하는 상황이면 전체를 탐색할 필요가 없이 투 포인터 알고리즘을 사용한다는 것을 알고 가자!
자세한 설명은 이분이 잘해주셨다. https://m.blog.naver.com/kks227/220795165570
*/

#pragma warning(disable:4996)

int N, Ary[10001], Count = 0;
long long S, Sum = 0;

/*
void DFS(int Cur, long long Sum) // 전체 탐색, 존나 느리다
{
    if (Cur == N) return;
    if (Visited[Cur + 1] == false)
    {
        Visited[Cur + 1] = true; DFS(Cur + 1, 0);
    }
    if (Sum + Ary[Cur] > S) return;
    if (Sum + Ary[Cur] == S) { Count++; return; }
    DFS(Cur + 1, Sum + Ary[Cur]);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> N >> S;
    for (int i = 0; i < N; i++)
    {
        cin >> Ary[i];
    }
    DFS(0, 0);
    cout << Count;
}

int main() // 이중 for문, 느리다
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> N >> S;
    for (int i = 0; i < N; i++)
    {
        cin >> Ary[i];
    }
    for (int i = 0; i < N; i++)
    {
        long long Sum = 0;
        for (int j = i; j < N; j++)
        {
            Sum = Sum + Ary[j]; 
            if (Sum == S) { Count++; break; }
            if (Sum > S) break;
        }
    }
    cout << Count;
}
*/

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> N >> S;
    for (int i = 0; i < N; i++)
        cin >> Ary[i];
    int Low = 0, High = 0;
    while (High < N || Sum >= S)
    {
        if (S == Sum) Count++;
        if (S <= Sum) Sum = Sum - Ary[Low++];
        else if (High < N) Sum = Sum + Ary[High++];
    }
    cout << Count;
}
