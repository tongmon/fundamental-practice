#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/12789
스택을 이용하는 문제다.
3
2 1 3
같은 경우 Nice가 나와야 하기에
스택에 잔려한 값들을 항상 보고 비울 수 있으면 비우는 것이 중요하다.
*/

int N, n, H = 1;
stack<int> A;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> n;
		if (H != n) { 
			while (!A.empty() && H == A.top()) {
				A.pop(), H++;
			}
			A.push(n);
		}
		else H++;
	}
	while (!A.empty() && H == A.top()) { 
		A.pop(), H++; 
	}
	cout << (A.empty() ? "Nice" : "Sad");
}