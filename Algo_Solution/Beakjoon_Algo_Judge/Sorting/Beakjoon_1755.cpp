#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1755
람다 정렬 연습.
*/

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	string A[] = { "zero","one","two","three","four","five","six","seven","eight","nine" };
	int N, M;
	cin >> N >> M;
	vector<int> K(M - N + 1);
	for (int i = N, j = 0; i <= M; i++)
		K[j++] = i;
	sort(K.begin(), K.end(), [&](int& a, int& b) {
		string x = to_string(a), y = to_string(b), X = A[x[0] - '0'], Y = A[y[0] - '0'];
		X += x.size() > 1 ? " " + A[x[1] - '0'] : "";
		Y += y.size() > 1 ? " " + A[y[1] - '0'] : "";
		return X < Y;
		});
	for (int i = 1; i <= K.size(); i++)
		cout << K[i - 1] << (i % 10 ? " " : "\n");
}