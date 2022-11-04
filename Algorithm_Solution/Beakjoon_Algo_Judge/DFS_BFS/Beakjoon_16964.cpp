#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/16964
DFS가 맞는지 판단하는 문제.
Set을 사용하여 해당 점에 특정 점이 연결되어있나 한 번에 판단해 나간다.
이 문제를 통해 구현속도를 늘려간다.
*/

int check[100001], N, I, a, b, Cnt;
vector<int> A;
unordered_set<int> G[100001];

void dfs(int x) {
	check[x] = 1;
	if (A[I++] == x)
		Cnt++;
back:
	if (I == N)
		return;
	if (G[x].find(A[I]) != G[x].end() && !check[A[I]]) {
		dfs(A[I]);
		goto back;
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N - 1; i++) {
		cin >> a >> b;
		G[a].insert(b);
		G[b].insert(a);
	}
	A.resize(N);
	for (int i = 0; i < N; i++)
		cin >> A[i];
	dfs(1);
	if (Cnt == N)
		cout << 1;
	else
		cout << 0;
}