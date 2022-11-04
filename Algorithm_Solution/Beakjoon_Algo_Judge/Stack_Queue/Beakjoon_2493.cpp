#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2493
스택 문제인데.. 시간초과 땜시 약간 애를 먹었다.
내 풀이는 약간 비효율적으로 푼 풀이이다.
새로 비교하게 되는 녀석은 현재 St_2에 있는 작은 녀석들을 pop하게 만들고
자신 보다 더 큰녀석을 만나거나 St_2가 비어있으면 St_2에 들어가고 다음 탑에 대해 비교를 진행한다.
비효율적인 이유는 값을 미리 다 받아 놓고 비교를 진행해서 값을 받는 시간과 출력을 하는 시간이 따로 존재하게 된다.
이 쓸모없는 두 개의 시간이 걸려 148ms라는 시간이 측정되었다.
저 두 시간을 없애는 방식은 그냥 입력을 받으면서 스택에 넣는 것이다.
스택이 비어있었다? 0 바로 출력
스택이 차있는데 들어올 녀석이 top보다 작다? top의 인덱스 출력
top보다 크다? 0 바로 출력하고 stack 비우기... 이런 방식이면 입력 받으면서 값을 출력해 조금 더 빨라진다... (112ms)
위와 같이 두 개의 방식을 모두 적어놓았다.
스택을 활용하는 문제인 것 같다면 새로 스택에 들어올 원소와 지금까지 스택에 넣어져 있는 원소 간의 관계를 잘 따져보자.
특히 top과의 비교도 중요하다. 그리고 스택에 삽입된 원소가 오름차순인지 내림차순인지도 한번 생각해보자!
이 문제를 통해 스택을 활용하는 능력을 길러간다.
*/

int N, num;
stack<pair<int, int>> St, St_2;
int Ary[500001];

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> num; St.push({ i, num });
    }
    for (int i = 0; i < N; i++)
    {
        while (!St_2.empty() && St_2.top().second <= St.top().second)
        {
            Ary[St_2.top().first] = St.top().first + 1;
            St_2.pop();
        }
        St_2.push(St.top()); St.pop();
    }
    while (!St_2.empty())
    {
        Ary[St_2.top().first] = 0;
        St_2.pop();
    }
    for (int i = 0; i < N; i++)
    {
        cout << Ary[i] << ' ';
    }
}

/*
int main(void) // 조금 더 빠른 풀이....
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> num;
        if (St.empty()) cout << 0 << ' ';
        else
        {
            while (!St.empty() && St.top().second <= num) St.pop();
            if (St.empty()) cout << 0 << ' ';
            else cout << St.top().first + 1 << ' ';
        }
        St.push({ i, num });
    }
}
*/