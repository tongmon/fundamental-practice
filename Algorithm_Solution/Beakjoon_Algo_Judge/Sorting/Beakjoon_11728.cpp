#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/11728
배열 합치는 문제다.
합병정렬에서 쓰이는 기법을 쓰면된다.
처음에는 multiset에다가 걍 다 때려넣는 방식으로 풀었는데 시간이 1000ms가 넘어가는 결과가 나와서
다시 생각해보니 multiset은 nlog(n)이고 밑의 합병정렬 방식은 n이여서 밑 방식이 더 효율적이다.
밑 풀이와 같이 비교해서 '어? 이 쪽이 더 크네?' 그러면 그 배열을 고르고 그 배열 인덱스 늘려주고... 이러한 방식을 기억하고 잘 써먹자!
*/

#pragma warning(disable:4996)

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int N, M, A_cur = 0, B_cur = 0; 
    cin >> N >> M;
    vector<int> A(N), B(M);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    for (int i = 0; i < M; i++)
    {
        cin >> B[i];
    }
    while (A_cur != N && B_cur != M)
    {
        if (A[A_cur] >= B[B_cur])
        {
            cout << B[B_cur++] << " ";
        }
        else
        {
            cout << A[A_cur++] << " ";
        }
    }
    for (int i = A_cur; i < N; i++)
    {
        cout << A[i] << " ";
    }
    for (int i = B_cur; i < M; i++)
    {
        cout << B[i] << " ";
    }
}