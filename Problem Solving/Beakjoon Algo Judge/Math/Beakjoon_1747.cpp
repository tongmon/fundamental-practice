#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1747
소수 판정법을 느릴 것 같아 에라토스테네스의 체로 풀었다.
나머지는 문자열 검사가 들어간다.
이 문제를 통해 구현 속도를 늘려간다.
*/

#define k 1003002
int P[k + 1] = { 1,1 }, N, u;

void func() {
	for (int i = 4; i <= k; i += 2)
		P[i] = 1;
	for (int i = 3; i <= sqrt(k); i += 2) {
		if (!P[i]) {
			for (int j = i * i; j <= k; j += i)
				P[j] = 1;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	func();
	for (int i = N; i <= k; i++) {
		if (!P[i]) {
			u = 1;
			string A = to_string(i);
			for (int j = 0; j < A.size() / 2 && u; j++) {
				if (A[j] != A[A.size() - j - 1])
					u = 0;
			}
			if (u) {
				cout << A;
				return 0;
			}
		}
	}
}