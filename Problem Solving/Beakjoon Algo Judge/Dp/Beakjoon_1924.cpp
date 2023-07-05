#include <iostream>
#include <string>
using namespace std;

// https://www.acmicpc.net/problem/1924
// 기초 출력 연습

int main()
{
    string buffer; bool flag = false;
    char month[3], date[3];
    int mindex = 0, dindex = 0;
    int Mary[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    string Dary[7] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };
    getline(cin, buffer);
    for (int i = 0; i < buffer.size(); i++)
    {
        if (buffer.at(i) == ' ')
        {
            flag = true;
        }
        else
        {
            if (flag == false)
            {
                month[mindex++] = buffer.at(i);
            }
            else
            {
                date[dindex++] = buffer.at(i);
            }
        }
    }
    month[mindex] = '\0'; date[dindex] = '\0';
    int M = atoi(month); int D = atoi(date);
    int sum = 0;
    for (int i = 0; i < M - 1; i++)
    {
        sum = sum + Mary[i];
    }
    sum = sum + D;
    cout << Dary[sum % 7];
}