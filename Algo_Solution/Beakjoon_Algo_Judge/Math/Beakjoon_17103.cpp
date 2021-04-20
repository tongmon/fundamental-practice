#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/17103
에라토스테네스의 체를 이용한 소수 구하기 문제다.
2 + 3 이나 3 + 2 나 같은 것으로 취급하기에 획득된 소수에서
주어진 수 / 2 만큼까지만 탐색해도 된다.
이 문제를 통해 구현 속도를 늘려간다.
*/

#define S 1000000
int Prime[S + 1] = { 1,1 }, T, N;
vector<int> P;

void P_M()
{
	for (int i = 4; i <= S; i += 2)
		Prime[i] = 1;
	for (int i = 3; i <= sqrt(S); i += 2) {
		if (Prime[i])
			continue;
		for (int j = i * i; j <= S; j += i)
			Prime[j] = 1;
	}
	P.reserve(80000);
	for (int i = 1; i <= S; i++)
		if (!Prime[i])
			P.push_back(i);
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> T;
	P_M();
	for (int i = 0; i < T; i++) {
		cin >> N;
		int Cnt = 0;
		for (auto& n : P) {
			if (n > N / 2)
				break;
			if (!Prime[N - n])
				Cnt++;
		}
		cout << Cnt << '\n';
	}
}