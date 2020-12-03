#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/14888
백트래킹 문제다.
연산자에 대해서 조합을 잘 하면 맞을 수 있다.
재귀적으로 풀어도 무방하나 C++에는 next_permutation이라는 강력한 함수가 있어서
이를 활용하여 풀었다.
이 문제를 통해 백트래킹 문제에 더 익숙해져간다.
*/

int N, In;
long long Min = 10e9 + 1, Max = -10e9 - 1;
vector<int> Num, Opr;

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> In;
		Num.push_back(In);
	}
	for (int i = 0; i < 4; i++)
	{
		cin >> In;
		for (int j = 0; j < In; j++)
		{
			Opr.push_back(i);
		}
	}
	do {
		long long A = Num[0];
		for (int i = 1; i < N; i++)
		{
			if (Opr[i - 1] == 0) {
				A += Num[i];
			}
			if (Opr[i - 1] == 1) {
				A -= Num[i];
			}
			if (Opr[i - 1] == 2) {
				A *= Num[i];
			}
			if (Opr[i - 1] == 3) {
				A /= Num[i];
			}
		}
		Min = min(A, Min); Max = max(A, Max);
	} while (next_permutation(Opr.begin(), Opr.end()));
	cout << Max << '\n' << Min;
}