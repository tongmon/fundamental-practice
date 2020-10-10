#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1018
브루트 포스로 접근해서 푸는 문제다.
처음에 격자가 나와서 DFS로 풀려했는데 코드가 늘어져서 생각을 고쳐먹고 간단하게 이중for문 박아버렸다.
돋보기 같이 8 * 8 격자를 기준으로 완전 탐색을 진행한다. 삼중for문이기는 하지만 최대 8 * 8 * 42 * 42 = 112896 이 정도라
1억번의 연산 = 1초 휴리스틱을 생각해보면 충분히 2초안에 실행이 가능하다.
격자 문제를 보면 무조건 DFS_BFS 부터 때리지 말고 생각을 좀 하고 문제에 접근하는 습관을 기르자...
*/

int Width, Height, W_cnt = 0, B_cnt = 0, Cnt = 1000;
char Board[51][51];

void Brute(int col, int row)
{
    W_cnt = B_cnt = 0;
    for (int i = col; i < col + 8; i++)
    {
        for (int j = row; j < row + 8; j++)
        {
            if ((i % 2 != j % 2) && Board[i][j] == 'B') B_cnt++;
            if ((i % 2 == j % 2) && Board[i][j] == 'W') B_cnt++;
            if ((i % 2 != j % 2) && Board[i][j] == 'W') W_cnt++;
            if ((i % 2 == j % 2) && Board[i][j] == 'B') W_cnt++;
            if (B_cnt > Cnt && W_cnt > Cnt) return;
        }
    }
}

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);   
    cin >> Height >> Width;
    for (int i = 0; i < Height; i++)
    {
        for (int j = 0; j < Width; j++)
        {
            cin >> Board[i][j];
        }
    }
    for (int i = 0; i < Height - 7; i++)
    {
        for (int j = 0; j < Width - 7; j++)
        {
            Brute(i, j);
            Cnt = min(min(Cnt, B_cnt), W_cnt);
        }
    }
    cout << Cnt;
}