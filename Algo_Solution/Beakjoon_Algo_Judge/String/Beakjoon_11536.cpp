#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/11536
vector도 operator==()이 정의되어있다.
편하게 써먹자
*/

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int N;
	cin >> N;
	vector<string> A(N), B;
	for (int i = 0; i < N; i++)
		cin >> A[i];
	B = A;
	sort(A.begin(), A.end());
	if (B == A) {
		cout << "INCREASING";
		return 0;
	}
	sort(A.begin(), A.end(), greater<string>());
	cout << (B == A ? "DECREASING" : "NEITHER");
}