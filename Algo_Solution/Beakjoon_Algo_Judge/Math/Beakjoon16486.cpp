#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/16486
원의 둘레를 구할 수 있으면 풀 수 있다.
*/

#define pi 3.141592

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	double N, M;
	cin >> N >> M;
	cout.precision(10);
	cout << 2 * N + 2 * pi * M;
}