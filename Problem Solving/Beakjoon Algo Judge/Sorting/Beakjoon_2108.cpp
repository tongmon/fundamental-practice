#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2108
개또라이 욕나오는 문제.
로직짜기 개쉬운데 진짜.... 하......
로직을 짜고 소수점 반올림에 대한 지식이 부족해서 푸는데 오래걸렸다...
이 문제에서 배운 굉장히 중요한 것은 (double)a / b의 값하고 (double)(a / b) 값하고 다르다는 것이다....
(double)a / b 가 실제 원하는 값이 나오고 (double)(a / b) 얘는 a / b에서 소수가 짤린 다음 실수 변환이 진행된다.
이것 땜시 겁나 시간 버렸다. 도대체 진짜.... 그나마 알아냈으니 다행이다.
그리고 정밀도를 위해서 float대신에 double을 애용하자!
그리고 반올림 함수 round 기억하자 아니면 내림함수 floor(a + 0.5)로 반올림 함수로 만들수 있다.

--------- 2023-07-11 ---------
재채점 후 틀려서 거의 3년만에 다시 풀었는데 과거의 위 설명을 보니 웃음만 나온다.
음수, 양수 반올림만 잘 구분해주면 풀 수 있다.
*/

int main()
{
    int n;
    unordered_map<int, int> m;
    cin >> n;
    vector<int> a(n), f;
    while (n--)
        cin >> a[n];
    sort(a.begin(), a.end());
    auto e = accumulate(a.begin(), a.end(), 0) / (double)a.size();
    for (const auto& i : a)
    {
        if (m.find(i) == m.end())
            m[i] = 0;
        n = max(n, ++m[i]);
    }
    for (const auto& i : m)
        if (i.second == n)
            f.push_back(i.first);
    sort(f.begin(), f.end());
    cout << (int)e + (e < 0 ? (int(e * 10) % 10 < -4 ? -1 : 0) : (int(e * 10) % 10 < 5 ? 0 : 1)) << '\n'
        << a[a.size() / 2] << '\n'
        << (f.size() > 1 ? f[1] : f[0]) << '\n'
        << a.back() - a.front();
}