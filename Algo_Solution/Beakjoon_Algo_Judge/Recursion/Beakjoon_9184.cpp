#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/9184
*/

int a, b, c, A, B, C, D;
map<tuple<int, int, int>, int> M;

int func(int i, int j, int k) {
	if (i <= 0 || j <= 0 || k <= 0)
		return 1;
	if (i > 20 || j > 20 || k > 20) {
		M[{ 20, 20, 20 }] = A = M.find({ 20,20,20 }) != M.end() ? M[{ 20, 20, 20 }] : func(20, 20, 20);
		return A;
	}
	if (i < j && j < k) {
		M[{i, j, k - 1}] = A = M.find({ i,j,k - 1 }) == M.end() ? func(i, j, k - 1) : M[{i, j, k - 1}];
		M[{i, j - 1, k - 1}] = B = M.find({ i,j - 1,k - 1 }) == M.end() ? func(i, j - 1, k - 1) : M[{i, j - 1, k - 1}];
		M[{i, j - 1, k}] = C = M.find({ i,j - 1,k }) == M.end() ? func(i, j - 1, k) : M[{i, j - 1, k}];
		return A + B - C;
	}
	M[{i - 1, j, k}] = A = M.find({ i - 1,j,k }) == M.end() ? func(i - 1, j, k) : M[{i - 1, j, k}];
	M[{i - 1, j - 1, k}] = B = M.find({ i - 1,j - 1,k }) == M.end() ? func(i - 1, j - 1, k) : M[{i - 1, j - 1, k}];
	M[{i - 1, j, k - 1}] = C = M.find({ i - 1,j,k - 1 }) == M.end() ? func(i - 1, j, k - 1) : M[{i - 1, j, k - 1}];
	M[{i - 1, j - 1, k - 1}] = D = M.find({ i - 1,j - 1,k - 1 }) == M.end() ? func(i - 1, j - 1, k - 1) : M[{i - 1, j - 1, k - 1}];
	return A + B + C - D;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> a >> b >> c;
	while (!(a == -1 && b == -1 && c == -1)) {
		cout << "w(" << a << ", " << b << ", " << c << ") = " << func(a, b, c) << '\n';
		cin >> a >> b >> c;
	}
}