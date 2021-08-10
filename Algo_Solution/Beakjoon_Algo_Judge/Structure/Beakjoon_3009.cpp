#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/3009
사각형이기에 숫자 쌍을 맞춰주면 된다.
*/

int x, y, A[2];
unordered_map<int, int> X, Y;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	for (int i = 0; i < 3; i++) {
		cin >> x >> y;
		X[x]++; Y[y]++;
	}
	for (auto& px : X) {
		if (px.second % 2)
			A[0] = px.first;
	}
	for (auto& py : Y) {
		if (py.second % 2)
			A[1] = py.first;
	}
	cout << A[0] << ' ' << A[1];
}