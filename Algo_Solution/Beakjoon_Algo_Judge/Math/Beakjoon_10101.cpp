#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/10101
if문 사용하면 풀린다.
*/

int A, B, C;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> A >> B >> C;
	if (A + B + C != 180)
		cout << "Error";
	else if (A == B && B == C)
		cout << "Equilateral";
	else if (A == B || B == C || C == A)
		cout << "Isosceles";
	else
		cout << "Scalene";
}