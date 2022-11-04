#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/9613
또 다른 최대공약수 문제이다. 
가능한 모든 수를 더해주면 된다.... 
그 합은 겁나 커질수 있으니 unsigned long long 형식 조심하고...
*/

#pragma warning(disable:4996)

unsigned long long Gcd(unsigned long long A, unsigned long long B) // 반복으로 작성
{
    unsigned long long Smallone = A > B ? B : A;
    unsigned long long Bigone = A > B ? A : B;
    unsigned long long R = Bigone % Smallone, temp;
    while (R != 0)
    {
        temp = R;
        R = Smallone % R;
        Smallone = temp;
    }
    return Smallone;
}

unsigned long long Sum(vector<int> *Container)
{
    unsigned long long First = 0, Second = 0, Sum = 0;
    for (int i = 0; i < Container->size() - 1; i++)
    {
        First = Container->at(i);
        for (int j = i + 1; j < Container->size(); j++)
        {
            Second = Container->at(j);
            Sum = Sum + Gcd(First, Second);
        }
    }
    Container->clear();
    return Sum;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    vector<int> Storage;
    vector<unsigned long long> Result;
    int N, subN, buffer;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> subN;
        for (int j = 0; j < subN; j++)
        {
            cin >> buffer; Storage.push_back(buffer);
        }
        Result.push_back(Sum(&Storage));
    }
    for (int i = 0; i < N; i++)
    {
        cout << Result[i] << "\n";
    }
}