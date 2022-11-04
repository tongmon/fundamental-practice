#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1780
분할정복 문제이다...
9개의 분할을 돌리면 된다. 분할 정복 유형이 처음이라 그런지 너무 잔실수가 많아서 오래걸렸다....
그리고 이차원 배열을 분할하는 방법도 미숙했던 것 같다.
이 문제 시작으로 분할 정복에 대한 문제의 감을 익혀나가야 되겠다.
문제를 접근하는 방식은 빠르게 알았지만 내 구현능력이 빠른시간에 이 문제를 풀기에 너무 딸렸다.
구현능력을 문제를 많이 풀어 기르자!
그리고 char형을 cin으로 받을 때 주의할 점은 내가 요번에 -1을 char형 배열에 cin으로 담으려 했는데 안되어서 보니...
-이랑 1을 따로 구분해서 받더라.... cin 사용시 유의하자
*/

#pragma warning(disable:4996)

short Paper[2200][2200];
int Minusone = 0, Zero = 0, One = 0;

void Counter(int left, int top, int right, int bottom)
{
    int Size = right - left + 1;
    int Hindex = top, Windex = left;
    if (Size == 3)
    {
        for (int i = top; i <= bottom; i++)
        {
            for (int j = left; j <= right; j++)
            {
                if (Paper[i][j] == 1)
                {
                    One++;
                }
                else if (Paper[i][j] == 0)
                {
                    Zero++;
                }
                else
                {
                    Minusone++;
                }
            }
        }
        return;
    }
    for (int k = 0; k < 9; k++)
    {
        bool is_block = true;
        for (int i = Hindex; i < Hindex + Size / 3; i++)
        {
            for (int j = Windex; j < Windex + Size / 3; j++)
            {
                if (Paper[i][j] != Paper[Hindex][Windex])
                {
                    Counter(Windex, Hindex, Windex + Size / 3 - 1, Hindex + Size / 3 - 1);
                    is_block = false; break;
                }
            }
            if (is_block == false)
            {
                break;
            }
        }
        if (is_block == true)
        {
            if (Paper[Hindex][Windex] == 1)
            {
                One++;
            }
            else if (Paper[Hindex][Windex] == 0)
            {
                Zero++;
            }
            else
            {
                Minusone++;
            }
        }
        Windex = Windex + Size / 3;
        if (k == 2 || k == 5)
        {
            Windex = left;
            Hindex = Hindex + Size / 3;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    short N; cin >> N; bool only_one = true;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> Paper[i][j];
            if (Paper[0][0] != Paper[i][j])
            {
                only_one = false;
            }
        }
    }
    if (only_one == true)
    {
        if (Paper[0][0] == 1)
        {
            cout << "0\n0\n1";
        }
        else if (Paper[0][0] == -1)
        {
            cout << "1\n0\n0";
        }
        else if (Paper[0][0] == 0)
        {
            cout << "0\n1\n0";
        }
    }
    else
    {
        Counter(0, 0, N - 1, N - 1);
        cout << Minusone << "\n" << Zero << "\n" << One;
    }
}