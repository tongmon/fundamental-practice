#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1037
정렬 후에 첫번째, 마지막 원소를 곱하면 원래 수가 나온다.
*/

long long A[51];

int main() 
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int N;
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> A[i];
	sort(A, A + N);
	cout << A[0] * A[N - 1];
}