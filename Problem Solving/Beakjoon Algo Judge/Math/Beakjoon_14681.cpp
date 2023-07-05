#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/14681
삼항 연산자를 적절히 이용하면 풀 수 있다.
*/

int a, b;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> a >> b;
	cout << (a * b > 0 ? (a > 0 ? 1 : 3) : (a < 0 ? 2 : 4));
}