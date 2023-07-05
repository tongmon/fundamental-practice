#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1212
또 다른 진수 변환 문제...
하드 코딩으로 001 010 011... 이렇게 작성하면 더 빠르겠지만 나는 8진수 한자리를 3개로 쪼개는 방식을 취했다.
*/

#pragma warning(disable:4996)

void Trans(string *Octa)
{
    if (*Octa == "0")
    {
        cout << 0; return;
    }
    char buffer;
    list<char> Binary;
    for (int i = Octa->size() - 1; i >= 0; i--)
    {
        buffer = Octa->at(i) - '0';
        for (int j = 0; j < 3; j++)
        {
            Binary.insert(Binary.begin(), (buffer % 2) + '0'); buffer = buffer / 2;
        }
    }
    if (Binary.front() == '0')
    {
        Binary.pop_front();
    }
    if (Binary.front() == '0')
    {
        Binary.pop_front();
    }
    for (auto iter = Binary.begin(); iter != Binary.end(); iter++)
    {
        cout << *iter;
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    string Number;
    cin >> Number;
    Trans(&Number);
}