#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1339
푸는데 정말 특이한 기믹이 필요한 문제였다...
이러한 사고방식을 더 빠르게 도출하도록 연습이 필요하다.
어떻게 풀었냐면 ABC + CES 라고 예를 들어보자 A는 일단 100이다. 100의 자리에 있으니까!
그럼 B는? 10이다. C는 어떻게 처리할까? C는 101이다. 1의 자리에도 100의 자리에도 모두 존재하니 말이다.
이렇게 값을 매겨진 알파벳들을 모두 계산한 다음에 내림차순 정렬을 해주면 가장 큰 수를 부여해야되는 녀석을 알 수가 있다.
위에서는 101(C) 100(A) 10(B) ... 이런 식이니 C에 가장 큰 9가 배정되어야 한다.
이렇게 자릿수를 배정하여 사용하는 방식을 알아두고 그리디 문제에 써먹자!
*/

int N, k, Digit[26];
string Ary[11];

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);   
    cin >> N; long long Sum = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> Ary[i]; k = 1;
        for (int j = Ary[i].size() - 1; j >= 0; j--, k = k * 10)
        {
            Digit[Ary[i][j] - 'A'] = Digit[Ary[i][j] - 'A'] + k;
        }
    }
    k = 9; sort(Digit, Digit + 26, greater<int>());
    for (int i = 0; i < 26 && Digit[i] != 0; i++)
    {
        Sum = Sum + Digit[i] * (k--);
    }
    cout << Sum;
}