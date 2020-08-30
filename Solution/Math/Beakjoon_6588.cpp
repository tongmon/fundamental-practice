#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/6588
골드바흐의 추측 문제이다.
이것 또한 소수에 관련된 문제이기에 에라토스테네스의 체를 잘 이용하면 손쉽게 접근 가능하다.
*/

#pragma warning(disable:4996)

int Num[1000001] = { 0,1,0, };

bool MakePrimeList(int End)
{
    for (int i = 2; i <= sqrt(End); i++)
    {
        for (int j = i * i; j <= End; j = j + i)
        {
            Num[j] = 1;
        }
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int buffer, bigone = -1; bool is_Wrong = true;
    vector<int> Storage;
    while (true)
    {
        cin >> buffer;
        if (buffer == 0)
        {
            break;
        }
        if (bigone <= buffer)
        {
            bigone = buffer;
        }
        Storage.push_back(buffer);
    }
    MakePrimeList(bigone);
    for (int i = 0; i < Storage.size(); i++)
    {
        buffer = Storage[i]; is_Wrong = true;
        for (int i = 3; i <= buffer / 2; i = i + 2)
        {
            if (Num[buffer - i] == 0 && Num[i] == 0)
            {
                cout << buffer << " = " << i << " + " << buffer - i << "\n";
                is_Wrong = false;
                break;
            }
        }
        if (is_Wrong == true)
        {
            cout << "Goldbach's conjecture is wrong.\n";
        }
    }
}