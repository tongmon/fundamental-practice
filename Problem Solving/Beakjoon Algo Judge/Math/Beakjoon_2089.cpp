#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2089
-2진수 문제이다.
푸는데 굉장히 어려웠다.... 
일단 % 연산에 대한 기본적인 이해가 필요하다. 
% 연산은 c++에서는 버림 방식이다. 이것이 무슨 말이냐 하면 7 % 2 = 3 * 2 + 1로 몫이 3이 나온다. 
7 % -2 = -3 * -2 + 1로 나온다. 
13 % -2 = -6.5 * -2 인데 .5를 버리기 때문에 -6 * -2 + 1이 된다.
이유는 7 / -2는 -3.xxx인데 버림 방식이기에 -4로 변한다. 이게 -4 * -2가 되는 것이다.
따라서 음수를 음수로, 양수를 양수로 나누면 문제가 없겠지만 음수를 양수와 양수를 음수와 나누는 순간 해석 차이가 발생한다.
이를 해결해 주어야 되는 문제다.
일단 진수 변환 문제이기에 어떤 수를 -2로 나누어야 하는건 알 수 있다.
이때 버림 방식에 따라 생기는 해석차이를 해결하려면 음수끼리 나뉘어 질 때 오히려 +1을 해주어야한다. 즉 올림을 해야한다.
쉽게 보면 우리가 원래 사용하던 이진수에서는 7을 2로 나누면 3.5여서 내림하여 3으로 만들었다.
근데 -2진수에서는 -7을 -2로 나누면 3.5인데 오히려 올려서 4로 만들어 주어야 한디.
이유는 잘은 모르지만 음수 진법이라서 오히려 올려야 하나보다.
이 문제를 통해 C++에서 나눗셈 연산에 대한 이해가 조금 올랐다.
*/

#pragma warning(disable:4996)

void MinusBinary(int k)
{
    if (k == 0)
    {
        cout << 0; return;
    }
    int Quot = k;
    list<short> Result;
    while (Quot != 0)
    {
        if (Quot < 0) // 음수일 경우에는 우리가 생각하는 몫과 다르다. 버림 방식을 사용하기 때문!
        {
            Result.insert(Result.begin(), -(Quot % -2));
            if (Quot % -2 == 0)
            {
                Quot = Quot / -2;
            }
            else
            {
                Quot = (Quot / -2) + 1; // 6.5가 몫이면 6으로 버리기 때문에 1을 오히려 더해준다. 올림해야 한다.
            }
        }
        else // 양수 일 경우에는 몫이 우리가 생각하는 일반적인 결과와 같게 나온다.
        {
            Result.insert(Result.begin(), Quot % -2);
            Quot = Quot / -2; // 7 / -2 는 -3.5인데 이것 또한 올려서 -3이 된다.
        }
    }
    for (auto iter = Result.begin(); iter != Result.end(); iter++)
    {
        cout << *iter;
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int N; cin >> N;
    MinusBinary(N);
}