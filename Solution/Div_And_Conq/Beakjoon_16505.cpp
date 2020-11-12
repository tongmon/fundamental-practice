#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

/*
https://www.acmicpc.net/problem/16505
재귀 함수 이용 출력 문제.
재귀 3분할해서 공백 잘 넣으면 풀린다.
재귀 출력 문제에 대해 좀 더 익숙해졌다.
*/

string A[1030];

void Printer(int Dep, int Line)
{
	if (Dep == 1)
	{
		A[Line].push_back('*'); A[Line].push_back('*');
		A[Line + 1].push_back('*');
		return;
	}
	Printer(Dep - 1, Line); 
	for (int i = 1; i <= pow(2, Dep - 1) - 1; i++)
	{
		for (int j = 0; j < i; j++)
		{
			A[Line + i].push_back(' ');
		}
	}
	Printer(Dep - 1, Line);
	Printer(Dep - 1, Line + pow(2, Dep - 1));
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int T; cin >> T;
	if (T == 0) { cout << '*'; return 0; }
	Printer(T, 0);
	for (int i = 0; i < pow(2, T); i++) cout << A[i] << '\n';
}
