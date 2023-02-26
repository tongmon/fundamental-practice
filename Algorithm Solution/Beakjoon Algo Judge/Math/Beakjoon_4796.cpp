#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/4796
수학 문제.
범위를 그려가며 생각해보면 풀 수 있다.
*/

int L, P, V, i = 1;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> L >> P >> V;
	while (L && P && V) {
		cout << "Case " << i << ": ";
		if (P - (((V / P) + 1) * P - V) <= L)
			cout << (V / P) * (L - P) + V << '\n';
		else
			cout << (V / P + 1) * L << '\n';
		cin >> L >> P >> V;
		i++;
	}
}