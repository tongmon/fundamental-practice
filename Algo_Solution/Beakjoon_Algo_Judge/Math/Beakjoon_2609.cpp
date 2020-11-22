#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2609
최대공약수, 최소공배수를 구하는 방법에 대한 문제이다.
유클리스 호제법을 모르고 풀었을 경우는 반복문으로 하나하나 검사 해가면서 찾기 때문에 비효율적이다.
유클리드 호제법을 알고 풀면? O(log(N))이라는 무친 속도가 나온다! 이를 잘 써먹도록...
원리는 이곳에 자세히 나와있다. -> https://ko.wikipedia.org/wiki/%EC%9C%A0%ED%81%B4%EB%A6%AC%EB%93%9C_%ED%98%B8%EC%A0%9C%EB%B2%95#.EC.95.8C.EA.B3.A0.EB.A6.AC.EC.A6.98
*/

#pragma warning(disable:4996)

int Gcd_Recur(int A, int B) // 재귀로 작성
{
    if (B == 0 || A == 0)
    {
        return A > B ? A : B;
    }
    int R = A % B;
    if (A < B)
    {
        R = B % A;
    }
    return Gcd_Recur((A > B ? B : A), R);
}

int Gcd(int A, int B) // 반복으로 작성
{
    int Smallone = A > B ? B : A;
    int Bigone = A > B ? A : B;
    int R = Bigone % Smallone, temp;
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
    int A, B, R;
    cin >> A >> B;
    R = Gcd(A, B);
    cout << R << "\n";
    cout << A * B / R;
}

/*
int main() // 내가 짠 무식한 방법... O(n)이 걸린다.
{
    ios::sync_with_stdio(false); cin.tie(0);
    int A, B;
    cin >> A >> B;
    int i = A < B ? A : B;
    while (i > 0)
    {
        if (A % i == 0 && B % i == 0)
        {
            break;
        }
        i--;
    }
    cout << i << "\n";
    cout << (A * B) / i;
}
*/