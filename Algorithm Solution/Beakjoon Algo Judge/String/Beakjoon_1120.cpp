#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1120
문자열 매칭을 완전 탐색으로 진행하면 된다.
*/

string A, B;
int D, K = 1e7;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> A >> B;
	for (int i = 0; i <= B.size() - A.size(); i++) {
		D = 0;
		for (int j = 0; j < A.size(); j++)
			if (A[j] != B[i + j]) D++;
		K = min(K, D);
	}
	cout << K;
}