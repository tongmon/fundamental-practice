#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/10430
말 그대로 나머지 연산 특성을 알기위한 문제
단순 출력 문제지만 꽤나 많이 쓰일 것 같아 느낀점을 적는다.
*/

#pragma warning(disable:4996)

int main()
{
    int A, B, C;
    cin >> A >> B >> C;
    cout << (A + B) % C << "\n";
    cout << ((A % C) + (B % C)) % C << "\n";
    cout << (A*B) % C << "\n";
    cout << ((A % C) * (B % C)) % C << "\n";
}