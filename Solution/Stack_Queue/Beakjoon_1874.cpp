#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1874
스택 문제...
스택을 좀만 활용할 줄 알면 풀 수 있다.
*/

int N, input, Max = 0;
vector<int> Ary; stack<int> Stack;
vector<char> Result;

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> input; Ary.push_back(input);
    }
    for (int i = 0; i < N; i++)
    {
        if (Stack.empty() || Ary[i] > Stack.top())
        {
            for (int j = Max + 1; j <= Ary[i]; j++)
            {
                Stack.push(j); Result.push_back('+');
            }
            Stack.pop(); Result.push_back('-'); Max = max(Ary[i], Max);
        }
        else if (Ary[i] == Stack.top())
        {
            Stack.pop(); Result.push_back('-');
        }
        else if (Ary[i] != Stack.top())
        {
            cout << "NO"; return 0;
        }
    }
    for (int i = 0; i < Result.size(); i++)
    {
        cout << Result[i] << '\n';
    }
}