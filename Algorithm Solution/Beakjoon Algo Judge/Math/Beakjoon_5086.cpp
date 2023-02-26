#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/5086
배수와 약수 문제.
졸작 끝나서 간단하게...
*/

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int A, B, C;
	string K[] = { "factor", "multiple", "neither" };
	while (1) {
		cin >> A >> B;
		if (!A) break;
		if (!(A % B)) C = 1;
		else if (!(B % A)) C = 0;
		else C = 2;
		cout << K[C] << "\n";
	}
}