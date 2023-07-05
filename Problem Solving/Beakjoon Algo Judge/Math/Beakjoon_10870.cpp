#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/10870
피보나치 수다.
여러 방식으로 짤 수 있지만 구현이 간단한 for문 방식을 사용했다.
사실 행렬 방식이 가장 빠르다.
*/

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int N; cin >> N;
	queue<int> Q;
	Q.push(0); Q.push(1);
	for (int i = 0; i < N; i++) {
		Q.push(Q.front() + Q.back());
		Q.pop();
	}
	cout << Q.front();
}