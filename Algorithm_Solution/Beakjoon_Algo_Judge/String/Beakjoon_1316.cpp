#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1316
전에 나왔던 단어를 기억하다가 새로운 단어가 등장하면
기억해둔 단어가 나왔다는 체크를 진행하면 된다.
*/

int A[26], N, Ans, b, k;
string a;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++) {
		memset(A, 0, sizeof(A));
		cin >> a;
		if (a.length() == 1) {
			Ans++;
			continue;
		}
		k = b = a[0];
		for (int i = 1; i < a.length() && k; i++) {
			if (A[a[i] - 'a']) k = 0;
			if (b != a[i]) {
				A[b - 'a'] = 1;
			}
			b = a[i];
		}
		if (k) Ans++;
	}
	cout << Ans;
}