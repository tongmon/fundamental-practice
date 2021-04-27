#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2529
재귀인데 방문 배열로 시간복잡도를 줄이는 유형이다
이 문제를 통해 구현 속도를 늘려간다.
*/

int N, V[10];
char a;
string A, Op, Min = "99999999999", Max = "0";
unordered_set<string> Vis;

void func(int Cur) {
	if (Cur == N + 1) {
		long long k = stoll(A);
		if (stoll(Min) > k)
			Min = A;
		if (stoll(Max) < k)
			Max = A;
		return;
	}
	for (int i = 0; i < 10; i++) {
		if (V[i])
			continue;
		A.push_back(i + '0'); V[i] = 1;
		if (!Cur)
			func(Cur + 1);
		else if (Vis.find(A) == Vis.end()) {
			if ((Op[Cur - 1] == '>' && A[Cur - 1] > A[Cur])
				|| (Op[Cur - 1] == '<' && A[Cur - 1] < A[Cur])) {
				Vis.insert(A);
				func(Cur + 1);
			}
		}
		A.pop_back(); V[i] = 0;
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> a;
		Op += a;
	}
	func(0);
	cout << Max << '\n' << Min;
}