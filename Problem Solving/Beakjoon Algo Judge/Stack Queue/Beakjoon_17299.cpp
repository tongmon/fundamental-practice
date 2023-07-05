#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/17299
스택을 사용하여 시간복잡도를 줄이는 문제.
오큰수 문제와 같은 원리여서 자세한 내용은 생략한다.
이 문제를 통해 구현 속도를 늘려간다.
*/

int F[1000001], In, N;
stack<pair<int, int>> St;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	vector<int> Ans(N), Con(N);
	for (int i = 0; i < N; i++) {
		cin >> In; F[In]++;
		Con[i] = In;
	}
	for (int i = 0; i < N; i++) {
		while (!St.empty() && St.top().first < F[Con[i]]) {
			Ans[St.top().second] = Con[i];
			St.pop();
		}
		St.push({ F[Con[i]], i });
	}
	while (!St.empty()) {
		Ans[St.top().second] = -1;
		St.pop();
	}
	for (auto& A : Ans)
		cout << A << ' ';
}