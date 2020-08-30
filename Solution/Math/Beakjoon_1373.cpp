#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1373
진수 변환 문제...
string형으로 삽입 삭제하니까 시간초과떠서 리스트로 바꾸니 작동 잘된다....
항상 삽입, 삭제 오버헤드 생각하면서 코딩짜자
*/

#pragma warning(disable:4996)

void Trans(string *Binary)
{
    int mult, counter, index = Binary->size() - 1, sum;
    list<char> buffer;
    while (index >= 0)
    {
        counter = 0, sum = 0; mult = 1;
        while (counter != 3 && index >= 0)
        {
            sum = sum + (Binary->at(index) - '0') * mult;
            mult = mult * 2; index--; counter++;
        }
        buffer.insert(buffer.begin(), sum + '0');
    }
    for (auto iter = buffer.begin(); iter != buffer.end(); iter++)
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