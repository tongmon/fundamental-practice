#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1978
기본적인 소수 판별 문제...
for()을 돌때에 인덱스를 5부터 시작하는 실수를 범했다.... 
5부터 시작하면 3으로 나뉘어 지는 홀수들은 어찌 알고.... 
아무튼 실수 잘 인지하고 다음부터 하지말자!
*/

#pragma warning(disable:4996)

bool is_Prime(short Num)
{
    if (Num == 1)
    {
        return false;
    }
    if (Num == 2 || Num == 3)
    {
        return true;
    }
    if (Num % 2 == 0) // 짝수는 소수가 아님
    {
        return false;
    }
    for (int i = 3; i <= Num / 2; i = i + 2)
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
    short N, buffer, count = 0; cin >> N;
    for (int i =0;i < N;i++)
    {
        cin >> buffer;
        if (is_Prime(buffer) == true)
        {
            count++;
        }
    }
    cout << count;
}