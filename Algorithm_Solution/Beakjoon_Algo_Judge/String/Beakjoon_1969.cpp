#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1969
문자열에 대해 브루트포스를 진행하면 된다.
*/

int N, M, Y, T;
char X;
vector<string> A;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	vector<string> A(N + 1);
	for (int i = 0; i < N; i++)
		cin >> A[i];
	for (int i = 0; i < M; i++) {
		map<char, int> V;
		for (int j = 0; j < N; j++)
			V.find(A[j][i]) != V.end() ? V[A[j][i]]++ : V[A[j][i]] = 1;
		Y = 0;
		for (auto& s : V) {
			if (Y < s.second) {
				Y = s.second;
				X = s.first;
			}
		}
		T += N - Y;
		A[N] += X;
	}
	cout << A[N] << '\n' << T;
}