#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1850
유클리드 호제법을 응용하는 문제이다.
A, B는 1로만 이루어 져있는 수이고 1이 몇개있는지 쓰여있다.
여기서 재밌는 사실은 1111 % 11 은 0이고 자리수로 따지면 4 % 2 = 0 과 같다.
111 % 11 은 1이고 자리수로 따지면 3 % 2 = 1 로 같다.
이를 보고 유추할 수 있는 것은 유클리드 호제법이 (A, 0) 이면 답이 최대공약수가 A가 되는데 1111, 11의 최대공약수가 11이며 4 % 2 = 0 이니
실제 자릿수를 나누며 도출된 수들은 그 수만큼의 자릿수를 가진 수라는 것이 된다.
말이 좀 어려운데 예를 들면 11111 % 11 에서 1이 나오는데 자릿수로 보면 5 % 2 해서 1이 나오니 1인 놈이 1개인 숫자, 1이 되는 것이고 한번 더 보면
11111 % 111 을 하면 실제수는 11이 나오고 자릿수로 보면 5 % 3 해서 2가 나오는 것이다.
자릿수로 유클리드 호제법을 해서 나온 나머지 수 만큼의 1을 가지고 있는 숫자를 우리가 연산으로 쓰고 있는 것이다.
따라서 자릿수 1 개수에 유클리드 호제법을 취하고 나온 개수가 최대공약수의 1의 개수가 된다.
*/

#pragma warning(disable:4996)

unsigned long long Gcd(unsigned long long A, unsigned long long B) // 반복으로 작성
{
    unsigned long long Smallone = A > B ? B : A;
    unsigned long long Bigone = A > B ? A : B;
    unsigned long long R = Bigone % Smallone, temp;
    while (R != 0)
    {
        temp = R;
        R = Smallone % R;
        Smallone = temp;
    }
    return Smallone;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    unsigned long long A, B;
    cin >> A >> B;
    unsigned long long num = Gcd(A, B);
    for (unsigned long long i = 0; i < num; i++)
    {
        cout << '1';
    }
}