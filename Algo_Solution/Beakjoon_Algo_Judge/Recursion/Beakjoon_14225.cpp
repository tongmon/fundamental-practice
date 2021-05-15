#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/14225
재귀를 통해 조합을 탐색하는 문제
원소가 많아야 20개 주어지기에 시간복잡도는 재귀로도 충분하다.
이 문제를 통해 구현속도를 늘려간다.
*/

bool V[2000001];
vector<int> A;
int N;

void func(int St, int Sum) {
	V[Sum] = 1;
	for (int i = St; i < N; i++)
		func(i + 1, Sum + A[i]);
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	A.resize(N);
	for (int i = 0; i < N; i++)
		cin >> A[i];
	func(0, 0);
	N = 1;
	while (V[N])
		N++;
	cout << N;
}