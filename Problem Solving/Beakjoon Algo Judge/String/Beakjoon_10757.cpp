#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/10757
긴 길이의 수를 더하는 로직
c++은 손수 짜줘야 한다.
*/

string A, B, C;

string Sum()
{
	if (A.size() < B.size())
		swap(A, B);
	int a = A.size() - 1, b = B.size() - 1, u = 0, p;
	for (; b >= 0; b--, a--) {
		p = A[a] + B[b] + u - 2 * '0';
		C += (p % 10 + '0');
		u = p / 10;
	}
	for (; a >= 0; a--) {
		p = u + A[a] - '0';
		C += (p % 10 + '0');
		u = p / 10;
	}
	if (u) C += '1';
	reverse(C.begin(), C.end());
	return C;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> A >> B;
	cout << Sum();
}