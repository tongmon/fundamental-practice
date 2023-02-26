#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/14889
*/

int Ary[20][20], Size, Min = 9999999, L_Sum, S_Sum;
vector<int> Team_L, Team_S;

void Chosen(int Start, int Cur)
{
    if (Cur == Size / 2)
    {
        L_Sum = S_Sum = 0;
        for (int i = 0; i < Size / 2 - 1; i++)
        {
            for (int j = i + 1; j < Size / 2; j++)
            {
                L_Sum = L_Sum + Ary[Team_L[i]][Team_L[j]] + Ary[Team_L[j]][Team_L[i]];
                S_Sum = S_Sum + Ary[Team_S[i]][Team_S[j]] + Ary[Team_S[j]][Team_S[i]];
            }
        }
        Min = min(Min, abs(L_Sum - S_Sum)); return;
    }
    for (int i = Start; i < Team_S.size(); i++)
    {
        Team_L.push_back(Team_S[i]); Team_S.erase(Team_S.begin() + i);
        Chosen(i, Cur + 1);
        Team_S.insert(Team_S.begin() + i, Team_L.back()); Team_L.pop_back();
    }
}

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> Size;
    for (int i = 0; i < Size; i++)
    {
        Team_S.push_back(i);
        for (int j = 0; j < Size; j++)
        {
            cin >> Ary[i][j];
        }
    }
    Chosen(0, 0); cout << Min;
}