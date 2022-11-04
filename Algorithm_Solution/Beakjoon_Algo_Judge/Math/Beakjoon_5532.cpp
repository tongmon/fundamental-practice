#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/5532
올림 연산을 사용하면 짧게 풀 수 있다.
*/

double L, A, B, C, D;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> L >> A >> B >> C >> D;
	cout << L - max(ceil(A / C), ceil(B / D));
}