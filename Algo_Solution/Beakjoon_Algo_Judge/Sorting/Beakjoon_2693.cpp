#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2693
정렬하여 N번째 큰 수를 구하는 것은
우선순위 큐를 사용하면 효율적으로 풀 수 있다.
*/

int N, A;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++) {
		priority_queue<int, vector<int>, greater<int>> Q;
		for (int j = 0; j < 10; j++) {
			cin >> A;
			Q.push(A);
			if (Q.size() > 3) Q.pop();
		}
		cout << Q.top() << '\n';
	}
}