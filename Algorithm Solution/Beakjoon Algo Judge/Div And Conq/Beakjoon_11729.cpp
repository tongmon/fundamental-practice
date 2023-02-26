#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/11729
재귀호출의 기초인 하노이탑 문제다. 분할정복에도 포함된다.
완전 기초 중의 기초니 원리부터 해서 빠삭하게 알고 넘어가자...
문제 푸는데 예전에 봤던거라 쉽겠네 했더니 정작 까먹어서 자괴감 느꼈다....
일단 A, B, C 라는 막대가 있을 것이다. 
A의 N개의 원판이 있다면 N-1 개의 원판을 B로 옮기고 C로 마지막 A에 남은 가장 큰 기저 원판을 옮긴다. 
그리고 옮겨 두었던 B에 있는 N-1개의 원판을 A를 이용하여 C로 옮기면 모두 A에서 C로 원판이 넘어가게 된다.
일단 옮기려면 매개체 막대가 중간에 있어야 한다는 것을 유의하고 위 단계들을 생각하면서 구현하면 될 것이다.
이 문제를 통해 까먹었던 하노이탑의 원리를 이해하고 Pair의 사용법을 익히고 간다.
문제를 작게 작게 쪼개어서 생각해보는 습관을 들이자.
*/

#pragma warning(disable:4996)

int Count = 0;
vector<pair<char, char>> Result;

void Hanoi(int N, char A, char B, char C)
{
    if (N == 1)
    {
        Count++; 
        Result.push_back(pair<char, char>(A, C));
        return;
    }
    Hanoi(N - 1, A, C, B);
    Count++;
    Result.push_back(pair<char, char>(A, C));
    Hanoi(N - 1, B, A, C);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int N; cin >> N;
    Hanoi(N, '1', '2', '3');
    cout << Count << "\n";
    for (int i = 0; i < Result.size(); i++)
    {
        cout << Result[i].first << " " << Result[i].second << "\n";
    }
}