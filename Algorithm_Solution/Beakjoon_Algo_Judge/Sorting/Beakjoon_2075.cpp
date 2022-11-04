#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2075
메모리 초과를 조심해야한다.
가장 큰 N개의 수만 유지하면 되는 문제...
(왜 빠르게 풀이 방법 생각이 안났을까...)
*/

int N, k;
priority_queue<int, vector<int>, greater<int>> Q;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			cin >> k;
			Q.push(k);
			if (Q.size() > N)
				Q.pop();
		}
	cout << Q.top();
}