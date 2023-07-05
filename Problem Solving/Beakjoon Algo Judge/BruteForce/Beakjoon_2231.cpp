#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2231
브루트포스 문제.
그냥 시간제한이 2초이고 while문 도중에 별다른 중단점 조건을 찾을 수가 없어서
브루트포스로 풀었다. 이러면 8ms가 소요된다.
다른 사람의 풀이를 보니 중단점 조건을 넣은 분이 있었다.
만약 256 이렇게 3자리라고 하면 자릿수로 최대로 우겨넣을 수 있는 9를 3자리이니 3번을 빼준다.
즉, 각 자릿수를 더한 수를 어떻게든 최대한 많이 뺀 녀석을 최하점으로 보고 input으로 들어온 값을 최대점으로 보며
탐색하는 방법이다.
이러면 0ms가 나온다.
*/

int Finder(int Num, int cnt)
{
    int Cur = Num, Buffer, Ans = 0, Sum;
    while (Cur > max(0, Num - 9 * cnt))
    {
        Buffer = Cur; Sum = 0;
        while (Buffer > 0)
        {
            Sum = Sum + Buffer % 10; 
            Buffer = Buffer / 10;
        }
        if (Sum + Cur == Num) Ans = Cur;
        Cur--;
    }
    return Ans;
}

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int N, k, a = 0; cin >> N; k = N;
    while (k > 0) { k = k / 10; a++; }
    cout << Finder(N, a);
}