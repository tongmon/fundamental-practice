#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1789
그리디라고 하는데 내가 보기엔 그냥 수학문제다.
n * (n+1) / 2  가 1 ~ n까지 합을 나타내니 그냥 이 값을 구하고
남는 값은 그냥 더 큰 자연수를 더한다 생각하면 된다.
이 문제를 통해 구현 속도를 늘려간다.
*/

long long N, K;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	while ((K * (K + 1) / 2) <= N)
		K++;
	cout << --K;
}