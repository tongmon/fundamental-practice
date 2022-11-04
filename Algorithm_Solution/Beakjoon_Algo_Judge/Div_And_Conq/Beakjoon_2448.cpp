#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2448
골드4짜리 별찍기 문제.
삼각형을 쪼개서 더 작은삼각형으로 재귀를 돌리면서 풀어야되는 문제다.
일단 N이라는 크기가 주어졌을때 그려지는 삼각형은 N/2짜리의 작은 서브 삼각형 3개로 나뉘고 가운데는 뻥 뚫려있다.
이 4개의 퍼즐을 잘 조합하여 구현하면 해결이 되는 문제다.
가장 작은 단위는 3이여서 여기서 재귀를 끊어주어야한다.
나는 삼각형 별찍어주는 부분과 공백 찍는 부분을 따로 구분해서 구했는데 다른 사람 풀이를 보니
미리 이차원배열을 크게 할당해놓고 각 삼각형의 꼭대기를 기점으로 재귀를 돌리는 방식을 썻다.
이 방식은 재귀함수 인자를 나 같이 라인을 넘기지 않고 좌표를 넘겨줘 x좌표를 기준으로 공백도 바로바로 처리가 가능해 숏코딩이 된다.
이러한 방식도 참고하자.
이 문제를 통해 재귀문제에 대한 감을 더 찾았다.
*/

#pragma warning(disable:4996)

vector<char> Line[3600];
vector<char> Space[3600];
int Size = 0;

void Printer(int N, int sline)
{
    if (N == 3)
    {
        Line[sline - 2].push_back('*');
        Line[sline - 1].push_back('*'); Line[sline - 1].push_back(' '); Line[sline - 1].push_back('*');
        for (int i = 0; i < 5; i++)
        {
            Line[sline].push_back('*');
        }
        return;
    }
    Printer(N / 2, sline);
    int buffer = 0;
    for (int i = 0; buffer != N / 2; i = i + 2, buffer++)
    {
        for (int j = 0; j <= i; j++)
        {
            Line[sline - buffer].push_back(' ');
        }
    }
    Printer(N / 2, sline);
    Printer(N / 2, sline - N / 2);
}

void SpaceMaker(int N)
{
    int buffer = N - 1;
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < buffer; j++)
        {
            Space[i].push_back(' ');
        }
        buffer--;
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int Size; cin >> Size;
    Printer(Size, Size - 1);
    SpaceMaker(Size);
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Space[i].size(); j++)
        {
            cout << Space[i][j];
        }
        for (int j = 0; j < Line[i].size(); j++)
        {
            cout << Line[i][j];
        }
        for (int j = 0; j < Space[i].size(); j++)
        {
            cout << Space[i][j];
        }
        cout << "\n";
    }
}