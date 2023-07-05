#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/3986
스택을 이용하면 손쉽게 풀린다.
*/

int N, Ans;
string A;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> A;
		stack<char> S;
		for (auto& n : A) {
			if (S.empty() || S.top() != n)
				S.push(n);
			else 
				S.pop();
		}
		if (S.empty()) Ans++;
	}
	cout << Ans;
}