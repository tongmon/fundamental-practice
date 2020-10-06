#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1182
간단한 조합 문제다.
DFS 방식으로 하나를 고르면 그 뒤에 있는 녀석들은 전부 무시하고 다음 녀석들 부터 탐색하는 순으로
계속 반복해서 진행한다.
다른 사람의 풀이를 보니 조합은 안쓰고 어떤 수를 선택하는 경우, 아닌 경우 이렇게 나누어 재귀를 돌렸다.
이런 브루트 포스적인 방식도 괜찮은 것 같다.
*/

#pragma warning(disable:4996)

int N, S, Ary[21], Count = 0;

/*
void dfs(int i, int sum)  // 브루트 포스 방식
{
    if (i == n) return;
    if (sum+arr[i] == s) cnt++;

    dfs(i+1, sum); // 선택 하는 경우
    dfs(i+1, sum + arr[i]); // 선택 안하는 경우
}
*/

void DFS(int Start, int Sum)
{
    if (Sum == S)
    {
        Count++;
    }
    for (int i = Start; i < N; i++)
    {
        DFS(i + 1, Sum + Ary[i]);
    }
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
    if (S == 0) cout << Count - 1;
    else cout << Count;
}