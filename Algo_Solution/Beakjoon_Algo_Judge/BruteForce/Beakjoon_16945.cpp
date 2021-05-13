#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/16945
1~9 순열을 돌려 탐색하면 되는 문제다.
*/

int sq[3][3], Min = 2e8, Q;
vector<int> P;

bool func() {
	Q = P[0] + P[4] + P[8];
	for (int i = 0; i < 3; i++) {
		int S = 0, K = 0;
		for (int j = 0; j < 3; j++) {
			S += P[i * 3 + j];
			K += P[i + j * 3];
		}
		if (S != Q || K != Q)
			return 0;
	}
	if (P[2] + P[4] + P[6] != Q)
		return 0;
	return 1;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			cin >> sq[i][j];
	for (int i = 1; i < 10; i++)
		P.push_back(i);
	do {
		if (!func())
			continue;
		int E = 0;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				E += abs(sq[i][j] - P[i * 3 + j]);
		Min = min(E, Min);
	} while (next_permutation(P.begin(), P.end()));
	cout << Min;
}