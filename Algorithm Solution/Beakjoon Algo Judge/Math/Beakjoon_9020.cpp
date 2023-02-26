#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/9020
에라토스테네스의 체를 사용하면 풀리는 문제
처음에 DP인줄 알았는데 소수 2개의 합이라 Dp도 필요없다는 것을 알았다.
*/

bool Pri[10001];
vector<int> Primes;

void Era() {
	for (int i = 4; i <= 10000; i+=2)
		Pri[i] = true;
	for (int i = 3; i <= 100; i += 2) {
		for (int j = i * i; j < 10001; j += i) {
			Pri[j] = true;
		}
	}
	for (int i = 2; i < 10001; i++)
	{
		if (!Pri[i]) Primes.push_back(i);
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int T, Num, Ans[2]; Era();
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> Num;
		for (auto p : Primes) {
			if (Num / 2 < p) break;
			if (!Pri[Num - p]) {
				Ans[0] = p; Ans[1] = Num - p;
			}
		}
		cout << Ans[0] << ' ' << Ans[1] << '\n';
	}
}