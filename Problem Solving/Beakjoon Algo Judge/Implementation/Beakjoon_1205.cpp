#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1205
구현 문제다.
등수를 구할 때 유의할 점은 같은 숫자가 있으면 같은 숫자들은 모두 같은 등수라는 것이다.
그 다음 다른 낮은 숫자가 나오면 해당 녀석은 같은 등수인 녀석들 때문에 등수가 확 내려간다.
*/

int main()
{
    int n, s, l, x, d, b = -1, g = 1;
    cin >> n >> s >> l;
    while (n--)
    {
        cin >> d;
        if (d == s && b != d)
            x = g;
        if (d < s)
            break;
        b = d;
        g++;
    }
    cout << (g > l ? -1 : (b == s ? x : g));
}