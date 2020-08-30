#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1929
에라토스테네스의 체 문제이다.
특정 수 1개가 소수인지 아닌지를 검사하는 법은 소수판별법을 통해 빠르게 할 수 있지만
그렇지 않고 M ~ N까지의 소수가 무었이 있는지를 판별하는 데에는 에라토스테네스의 체가 훨씬 효율적이다.
밑에도 보면 is_Prime으로 실행시에 128ms가 걸렸다.
하지만 에라토스테네스의 체 방식을 사용하면 굉장히 빠르게 20ms에 끝났다...
따라서 소수 판별 문제가 나오면 에라토스테네스의 체, 소수판별법을 생각해보자.
에라토스테네스의 체는 구현하기 초반에 조금 까다로웠는데 2의 배수들을 지우고 3의 배수를 지울 경우에
중복이 되는 경우들 ex) 6 이런 애들을 어떻게 건너뛰지? 라고 생각했더니 무조건 검사를 i*i부터 시행하면 되는 것이였다.
그니까 3은 9부터 제거 5는 25부터 제거 7은 49부터 제거.... 이러한 방식으로 하면 된다.
배울 것이 상당히 많은 문제이다.
내가 배운 사이트: https://ko.khanacademy.org/computing/computer-science/cryptography/comp-number-theory/a/comp-number-theory-introduction
*/

#pragma warning(disable:4996)

int Num[1000001] = { 0,1,0, }; // 1이면 합성수 0이면 소수 / 1, 2는 미리 세팅

void Eratosthenes(int start, int end)
{
    for (int i = 2;i <= sqrt(end);i++)
    {
        for (int j = i * i; j <= end; j = j + i)
        {
            Num[j] = 1;
        }
    }
    for (int i = start; i <= end; i++)
    {
        if (Num[i] == 0)
        {
            cout << i << "\n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int start, end;
    cin >> start >> end;
    Eratosthenes(start, end);
}

/*
bool is_Prime(int Num) // 이 판별법에서 더 빠르게 하려면 미리 계산되어 있는 소수 테이블이 필요하다.
{
    if (Num == 1)
    {
        return false;
    }
    if (Num == 2)
    {
        return true;
    }
    if (Num % 2 == 0)
    {
        return false;
    }
    for (int i = 3; i <= sqrt(Num); i = i + 2)
    {
        if (Num % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int start, end, j;
    cin >> start >> end;
    for (int i = start; i <= end; i++)
    {
        if (is_Prime(i) == true)
        {
            cout << i << "\n";
        }
    }
}
*/