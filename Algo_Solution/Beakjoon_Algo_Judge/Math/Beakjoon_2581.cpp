#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2581
에라토스테네스의 체를 이용하면 쉽게 접근 가능한 문제다.
*/

int M, N, p[10001] = { 1,1 }, Min, S;

void func()
{
	for (int i = 4; i <= N; i += 2)
		p[i] = 1;
	for (int i = 3; i <= sqrt(N); i += 2) {
		if (p[i]) continue;
		for (int j = i * i; j <= N; j += i)
			p[j] = 1;
	}
	for (int i = M; i <= N; i++) {
		if (p[i]) continue;
		if (!S)
			Min = i;
		S += i;
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> M >> N;
	func();
	if (!S) cout << -1;
	else cout << S << '\n' << Min;
}