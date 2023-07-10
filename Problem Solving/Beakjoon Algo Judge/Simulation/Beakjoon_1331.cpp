/*
https://www.acmicpc.net/problem/1331
나이트로 체스판을 순회하는 문제.
나이트의 이동 방식인지 체크하고 이미 갔던 곳을 다시 가려하는지 체크, 마지막에는 시작점으로 회귀할 수 있는지 체크하면 된다.
*/

#include <bits/stdc++.h>
using namespace std;

#define v(l, p) (abs(l[0] - p[0]) != 2 || abs(l[1] - p[1]) != 1) && (abs(l[0] - p[0]) != 1 || abs(l[1] - p[1]) != 2)

bool b[6][6];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string l, p, s;
    for (int i = 0; i < 36; i++)
    {
        cin >> l;
        if (!i)
            s = l;
        if (b[l[0] - 'A'][l[1] - '1'] || (i && v(l, p)))
        {
            p[0] = 1;
            break;
        }
        b[l[0] - 'A'][l[1] - '1'] = 1;
        p = l;
    }
    cout << (p[0] == 1 || v(l, s) ? "Invalid" : "Valid");
}