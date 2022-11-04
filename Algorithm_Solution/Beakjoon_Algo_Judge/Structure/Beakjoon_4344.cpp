#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/4344
그냥 소수점 몇자리까지 잘 맞춰줘야 하는 문제로
fixed, precision을 잘 사용하면 된다.
*/

double T, N, M, J;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> T;
	cout << fixed;
	cout.precision(3);
	for (int i = 0; i < T; i++) {
		cin >> N;
		vector<double> V(N);
		J = M = 0;
		for (int j = 0; j < N; j++) {
			cin >> V[j];
			M += V[j];
		}
		M /= N;
		for (auto& a : V)
			if (M < a) J++;
		cout << round(J * 1e2 / N * 1e3) / 1e3 << "%\n";
	}
}