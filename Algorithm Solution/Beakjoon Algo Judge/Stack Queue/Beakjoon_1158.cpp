#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/1158
약간 원형 큐의 원리를 이용한 문제다.
% 연산자를 생각하면서 짜는 습관을 기르자
*/

#pragma warning(disable:4996)

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int N, K, index; vector<int> Circle;
    cin >> N >> K; 
    index = K - 1;
    for (int i = 0; i < N; i++)
    {
        Circle.push_back(i + 1);
    }
    cout << "<";
    for (int i = 0; i < N - 1; i++)
    {
        cout << Circle[index] << ", "; 
        Circle.erase(Circle.begin() + index); 
        if (index == 0)
        {
            index = Circle.size() - 1;
        }
        else
        {
            index--;
        }
        index = (index + K) % Circle.size();
    }
    cout << Circle[index] << ">";
}