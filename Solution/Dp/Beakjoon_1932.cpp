#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cstring>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1932
삼각형 구조를 이해하고 Dp배열을 잘 설계하면 풀 수 있는 문제.
임의의 Dp 배열 요소는 윗 단계의 왼쪽 부모, 오른쪽 부모를 타고 내려오게 될 것이고 
둘 다 저장할 필요없이 둘 중에 큰 루트를 선택하여 저장하면 된다.
*/

int T, MAX = 0, input;
int DP[1002][502]; // 인덱스, 레벨

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        int j = 501 - i;
        while (j <= 501 + i)
        {
            cin >> input;
            if (i == 0) DP[j][i] = input;
            else
            {
                DP[j][i] = max(DP[j - 1][i - 1], DP[j + 1][i - 1]) + input;
            }
            if (T - 1 == i) MAX = max(DP[j][i], MAX);
            j = j + 2;
        }
    }
    cout << MAX;
}