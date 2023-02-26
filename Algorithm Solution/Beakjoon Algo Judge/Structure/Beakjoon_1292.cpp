#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1292
주어진 그대로 구현을 하면 풀리는 문제다.
*/

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int i = 1, A, B, Ans = 0;
	vector<int> k;
	while (k.size() < 1001) {
		for (int j = 0; j < i; j++)
			k.push_back(i);
		i++;
	}
	cin >> A >> B;
	for (int p = A - 1; p < B; p++)
		Ans += k[p];
	cout << Ans;
}