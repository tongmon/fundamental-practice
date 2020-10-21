#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/14492
행렬곱에 대한 수학 문제이다.
부울곱이기에 비트연산을 활용해야 한다.
*/

short Mat[2][301][301], Size;
int Count = 0;

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> Size;
    for (int k = 0; k < 2; k++)
    {
        for (int i = 0; i < Size; i++)
        {
            for (int j = 0; j < Size; j++)
            {
                cin >> Mat[k][i][j];
            }
        }
    }
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            short Buffer = 0;
            for (int k = 0; k < Size; k++)
            {
                Buffer = Mat[0][i][k] == 1 && Mat[1][k][j] == 1 ? Buffer | 1 : Buffer | 0;
            }
            if (Buffer == 1) Count++;
        }
    }
    cout << Count;
}