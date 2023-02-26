#include <bits/stdc++.h>
using namespace std;

/*
* https://www.acmicpc.net/problem/1935
cout << fixed; 라는 소숫점을 고정하는 기법을 처음 알아간다.
이를 기억하도록...
그 외에는 평범한 후위표기식 문제다.
이 문제를 통해 소수점 고정법을 알아간다.
*/

int N, Ary[26];
string Str;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> Str;
	for (int i = 0; i < N; i++)
		cin >> Ary[i];
	stack<double> St;
	for (auto& s : Str) {
		if ('A' <= s && s <= 'Z')
			St.push(Ary[s - 'A']);
		else {
			double A = St.top(), B; St.pop();
			B = St.top(); St.pop();
			if (s == '*')
				St.push(A * B);
			else if (s == '+')
				St.push(A + B);
			else if (s == '-')
				St.push(B - A);
			else
				St.push(B / A);
		}
	}
	cout << fixed;
	cout.precision(2);
	cout << St.top();
}