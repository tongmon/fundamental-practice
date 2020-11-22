#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cstring>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/2504
반례가 많은 구현 + 스택 문제다.
나는 반례에서 고통받기 보다는 개뻘짓을 해서 고통받았다...
용량을 좀더 줄이려고 short를 쓰는 바람에 오버플로우가 생겨 자꾸 오답처리가 되어 빡쳤다.
앞으로 문제 풀 때 최대로 나올 수 있는 값을 잘 생각하면서 자료형을 정하자... 
괜히 용량 줄이려고 객기 부리지 말고
*/

string input;
stack<pair<int, char>> Stock;

bool Diff(char O, char E, short Num, int i)
{
    int Sum = 0;
    if (input[i] == O && Stock.empty()) return false;
    if (input[i] == O && Stock.top().second == E)
    {
        Stock.pop(); Stock.push({ Num, '|' });
    }
    else if (input[i] == O && Stock.top().second != E)
    {
        while (!Stock.empty() && Stock.top().second != E)
        {
            if (Stock.top().second != '|') return false;
            Sum = Sum + Stock.top().first * Num; Stock.pop();
        }
        if (Stock.empty()) return false;
        Stock.pop(); Stock.push({ Sum, '|' });
    }
    return true;
}

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> input; int Ans = 0;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == '(') Stock.push({ 2, '(' });
        else if (input[i] == '[') Stock.push({ 3, '[' });
        if (!Diff(')', '(', 2, i)) { cout << 0; return 0; }
        if (!Diff(']', '[', 3, i)) { cout << 0; return 0; }
    }
    while (!Stock.empty())
    {
        if (Stock.top().second != '|') { cout << 0; return 0; }
        Ans = Ans + Stock.top().first;
        Stock.pop();
    }
    cout << Ans;
}