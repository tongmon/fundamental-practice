#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/11170
람다 함수 연습할 겸 풀어본 문제다.
나머지 연산을 이용하면 된다.
*/

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int A, T, N, M;
	cin >> T;
	for (int i = 0; i < T; i++) {
		A = 0;
		cin >> N >> M;
		for (int j = N; j <= M; j++) {
			[&A](int k)->void {if (!k) A++; while (k) { A += k % 10 ? 0 : 1; k /= 10; }}(j);

			/*
			// 람다를 안 쓴 코드
			if (!j) A++;
			else {
				int P = j;
				while (P) {
					A += P % 10 ? 0 : 1;
					P /= 10;
				}
			}
			*/
		}
		cout << A << '\n';
	}
}