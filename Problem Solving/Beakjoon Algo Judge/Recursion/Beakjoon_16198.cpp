#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/16198
재귀를 통해 반복 선택을 하면 되는 문제다.
지우는 순서에 따라 결과가 달라지기에 조합이 아닌 순열을 구현해야 한다.
이 문제로 구현 속도를 늘려간다.
*/

int N, Max;
vector<int> A;

void func(int s) {
	if (A.size() == 2) {
		Max = max(Max, s);
		return;
	}
	for (int i = 1; i < A.size() - 1; i++)
	{
		int b = A[i]; A.erase(A.begin() + i);
		func(s + A[i] * A[i - 1]);
		A.insert(A.begin() + i, b);
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	A.resize(N);
	for (int i = 0; i < N; i++)
		cin >> A[i];
	func(0);
	cout << Max;
}