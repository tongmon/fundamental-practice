#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/9184
재귀호출 줄이기 위해 DP를 사용하는 문제다.
맵을 이용하여 DP를 구현했다.
재귀시 전역 변수 사용을 주의해야 한다.
잘 못 사용하면 반환 값이 이상해질 수 있다.
이 문제를 통해 구현속도를 늘려간다.
*/

using tup = tuple<int, int, int>;
tup R[] = { {0,0,-1},{0,-1,-1},{0,-1,0},{-1,0,0},{-1,-1,0},{-1,0,-1},{-1,-1,-1},{20,20,20} };
map<tup, int> M;

int func(tup K) {
	int A[4], a = get<0>(K), b = get<1>(K), c = get<2>(K);
	if (a <= 0 || b <= 0 || c <= 0)
		return 1;
	if (a > 20 || b > 20 || c > 20) {
		M[R[7]] = A[0] = M.find(R[7]) != M.end() ? M[R[7]] : func(R[7]);
		return A[0];
	}
	if (a < b && b < c) {
		for (int i = 0; i < 3; i++) {
			tup B = { a + get<0>(R[i]),b + get<1>(R[i]),c + get<2>(R[i]) };
			M[B] = A[i] = M.find(B) == M.end() ? func(B) : M[B];
		}
		return A[0] + A[1] - A[2];
	}
	for (int i = 3; i < 7; i++) {
		tup B = { a + get<0>(R[i]),b + get<1>(R[i]),c + get<2>(R[i]) };
		M[B] = A[i - 3] = M.find(B) == M.end() ? func(B) : M[B];
	}
	return A[0] + A[1] + A[2] - A[3];
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int a, b, c;
	cin >> a >> b >> c;
	while (!(a == -1 && b == -1 && c == -1)) {
		cout << "w(" << a << ", " << b << ", " << c << ") = " << func({ a, b, c }) << '\n';
		cin >> a >> b >> c;
	}
}