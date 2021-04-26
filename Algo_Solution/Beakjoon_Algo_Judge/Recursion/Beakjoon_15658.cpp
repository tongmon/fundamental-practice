#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/15658
재귀를 이용하는 순열 문제 비스무리한데
시간복잡도를 줄이기 위해 방문배열을 사용해야 한다.
set을 이용해여 예전에 갔던 녀석들의 방문을 방지했다.
이 문제를 통해 구현 속도를 늘려간다.
*/

int N, In, Min = 2e9, Max = -2e9;
vector<int> A, P, Sel;
unordered_set<long long> Vis;

void func(int Cur, long long Sum, long long n)
{
	if (Cur == N - 1) {
		int R = A[0];
		for (int i = 0; i < Sel.size(); i++) {
			if (Sel[i] == 1)
				R += A[i + 1];
			else if (Sel[i] == 2)
				R -= A[i + 1];
			else if (Sel[i] == 3)
				R *= A[i + 1];
			else if (Sel[i] == 4)
				R /= A[i + 1];
		}
		Min = min(Min, R);
		Max = max(Max, R);
		return;
	}
	for (int i = 0; i < P.size(); i++) {
		Sum += n * P[i];
		if (Vis.find(Sum) == Vis.end()) {
			Vis.insert(Sum);
			Sel.push_back(P[i]); P.erase(P.begin() + i);
			func(Cur + 1, Sum, n * 10);
			P.insert(P.begin() + i, Sel.back()); Sel.pop_back();
		}
		Sum -= n * P[i];
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> In;
		A.push_back(In);
	}
	for (int i = 0; i < 4; i++) {
		cin >> In;
		for (int j = 0; j < In; j++)
			P.push_back(i + 1);
	}
	func(0, 0, 1);
	cout << Max << '\n' << Min;
}