#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/10431
삽입 정렬 비스무리한 문제
실제 정렬을 할 필요는 없고 자기보다 키가 큰 녀석들은 어짜피 뒤로 물러서줘야 하기에 자기보다 큰 녀석들이 몇명 있는지만 세주면 된다.
*/

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int p, q, r;
    cin >> p;
    while (p--)
    {
        cin >> q;
        vector<int> a(20);
        for (auto &t : a)
            cin >> t;
        r = 0;
        for (int j = 1; j < 20; j++)
        {
            for (int k = j - 1; k >= 0; k--)
                if (a[j] < a[k])
                    r++;
        }
        cout << q << ' ' << r << '\n';
    }
}