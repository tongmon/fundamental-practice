#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/17087
최대공약수를 이용하는 문제다.
N개의 수에 대한 최대공약수는 수를 2개씩 잡아서 최대공약수를
구하는 짓을 계속 반복하면 된다.
이 문제를 통해 구현 속도를 늘려간다.
*/

int N, A, F, K;

int gcd(int a, int b) {
	if (!b)
		return a;
	return gcd(b, a % b);
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> A >> F;
	F = abs(A - F);
	for (int i = 1; i < N; i++) {
		cin >> K;
		K = abs(A - K);
		F = gcd(max(F, K), min(F, K));
	}
	cout << F;
}