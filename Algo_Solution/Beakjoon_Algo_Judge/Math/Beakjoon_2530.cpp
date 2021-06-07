#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2530
% 연산을 잘 사용하면 풀 수 있는 문제다.
*/

int N, M, K, P, h = 3600, m = 60;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M >> K >> P;
	int t = (N * h + M * m + K + P) % 86400;
	cout << t / h << ' '; t %= h;
	cout << t / m << ' '; cout << t % m;
}