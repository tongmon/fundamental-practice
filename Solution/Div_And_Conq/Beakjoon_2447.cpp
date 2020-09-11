#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2447
재귀를 이용한 별찍기 문제다.
처음에 문자 출력시에 커서 옮기는 기능은 window.h에 있는데 안사용하고 어케풀까 고민이 되었는데
따로 라인에 그려질 녀석들을 저장해놓는 버퍼를 두면 해결되는 것이였다...
이런 출력문제는 라인 버퍼를 사용하는 것을 항상 고려해보자.
문제의 원리를 간략하게 설명해보면 항상 N/3 크기에 해당되는 블록이 8개가 존재하고 가운데가 그 크기만큼 뚫려있다.
그 9개 합해져서 N 크기의 블록을 구성하는데 처음 3개의 N/3들이 출력 라인이 같고 마지막 3개의 N/3 블록들이 출력 라인이 서로 같다.
그 2개 묶어서 재귀돌리고 남은건 가운데 라인... 그것도 남은 것 고려해서 재귀 2개 돌리고 공백은 따로 출력해주면 해결된다.
이 문제를 통해 분할정복 문제에 대한 감을 잡아간다.
*/

#pragma warning(disable:4996)

vector<char> Line[2200];

void Star_Printer(int N, int sline)
{
    if (N == 3)
    {
        Line[sline].push_back('*'); Line[sline].push_back('*'); Line[sline].push_back('*');
        Line[sline + 1].push_back('*'); Line[sline + 1].push_back(' '); Line[sline + 1].push_back('*');
        Line[sline + 2].push_back('*'); Line[sline + 2].push_back('*'); Line[sline + 2].push_back('*');
        return;
    }
    for (int i = 0; i < 3; i++)
    {
        Star_Printer(N / 3, sline);
    }
    Star_Printer(N / 3, sline + N / 3);
    for (int i = 0; i < N / 3; i++)
    {
        for (int j = 0; j < N / 3; j++)
        {
            Line[sline + i + N / 3].push_back(' ');
        }
    }
    Star_Printer(N / 3, sline + N / 3);
    for (int i = 0; i < 3; i++)
    {
        Star_Printer(N / 3, sline + (N / 3) * 2);
    }
    return;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int N; cin >> N;
    Star_Printer(N, 0);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << Line[i][j];
        }
        cout << "\n";
    }
}