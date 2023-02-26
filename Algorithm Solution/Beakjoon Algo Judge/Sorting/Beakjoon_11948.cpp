#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/11948
정렬하면 쉽게 풀 수 있다.
*/

int main() 
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int A[6];
	for (int i = 0; i < 6; i++) {
		cin >> A[i];
	}
	sort(A, A + 4);
	cout << A[3] + A[1] + A[2] + max(A[4], A[5]);
}