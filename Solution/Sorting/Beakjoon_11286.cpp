#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/11286
힙의 비교 연산을 입맛에 맞게 조절할 수 있는지 묻는 문제다.
여기서 struct를 사용해 비교 연산을 정의하는 방법을 익히고 간다.
밑의 Cmp를 보면서 비교 연산 정의에 대한 감을 익히자.
*/

struct Cmp
{
    bool operator()(int a, int b)
    {
        if (abs(a) == abs(b)) return a > b;
        return abs(a) > abs(b);
    }
};

priority_queue<int, vector<int>, Cmp> absQ;
int input;

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int N; cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> input;
        if (input == 0 && absQ.empty() == false) { cout << absQ.top() << '\n'; absQ.pop(); }
        else if (input == 0 && absQ.empty()) cout << 0 << '\n';
        else absQ.push(input);
    }
}