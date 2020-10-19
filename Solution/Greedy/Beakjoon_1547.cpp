#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1541
골때리는 greedy 문제였다...
처음엔 그냥 -면 괄호치고 다음 - 나오면 닫는 괄호쳐서 더해가는 방식으로 풀려했으나...
더 생각해보니 -가 한번이라도 나오면 그 뒤는 모두 빼기가 가능해진다.
그래서 걍 그렇게 풀었다.
그리고 문자를 숫자로 변환하는 함수 직접 짜서 썼는데 이거 stoi쓰면 편해진다.
stoi로 스트링 숫자로 변환해주는 함수 기억하고 써먹자!
*/

int Ans;
string input;
vector<int> Num;

int Convert()
{
    int Sum = 0, k = 1;
    for (int i = Num.size() - 1; i >= 0; i--, k = k * 10)
    {
        Sum = Sum + Num[i] * k;
    }
    Num.clear(); return Sum;
}

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> input; bool is_minus = false;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == '-' || input[i] == '+')
        {
            Ans = is_minus == false ? Ans + Convert() : Ans - Convert();
            if (input[i] == '-') is_minus = true;
        }
        else Num.push_back(input[i] - '0');
    }
    Ans = is_minus == false ? Ans + Convert() : Ans - Convert();
    cout << Ans;
}