#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/10610
간단한 그리디 문제다.
일단 30배수가 되는 조건은 3의 배수와 10의 배수 두가지 조건을 모두 만족하면 된다.
3의 배수는 자릿수의 합이 3의 배수면 되고, 10의 배수는 마지막이 무조건 0이면 된다.
최대수를 구하는 것이기 때문에 내림차순 정렬하고 이게 답인지 아닌지 판단하면 된다.
*/

#pragma warning(disable:4996)

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string buffer; int sum = 0;
    cin >> buffer;
    sort(buffer.begin(), buffer.end(), greater<char>());
    for (int i = 0; i < buffer.size(); i++)
    {
        sum = sum + (buffer[i] - '0');
    }
    if (sum % 3 == 0 && buffer.back() == '0')
    {
        cout << buffer;
    }
    else
    {
        cout << -1;
    }
}