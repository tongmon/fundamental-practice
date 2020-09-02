#include <iostream>
#include <cstring>
#include <list>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1676
팩토리얼 응용 문제이다.
0이 아닌 숫자가 첫 등장하는 자릿수 까지 0이 몇번 나오는지 구하는 문제인데...
결국 10이 몇번 곱해졌나를 묻는 문제이다. 10은 2와 5의 조합이고 즉 2, 5로 이루어진 수들이
몇번 나오고 2, 5를 세며 2, 5 중 더 적은 수의 값이 10이 몇번 곱해졌는지를 뜻한다.
근데 해보면 알겠지만 2의 약수는 사실 카운트 해줄 필요가 없다. 
5만 세도 되는게 2보다 5가 항상 적게 나오기 때문
*/

#pragma warning(disable:4996)

int facto_re(int N)
{
    if (N == 0)
    {
        return 0;
    }
    int two = 0, five = 0, i = 1, buffer;   
    while (i != N + 1)
    {
        buffer = i;
        while (buffer % 2 == 0)
        {
            two++; buffer = buffer / 2;
        }
        while (buffer % 5 == 0)
        {
            five++; buffer = buffer / 5;
        }
        i++;
    }
    return two > five ? five : two;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int N; cin >> N;
    cout << facto_re(N);
}