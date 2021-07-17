#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/13458
ceil 쓰니까 틀리는데 왜 그런지 모르겠다.
나머지 있는 경우에 1을 더하는 방식으로 풀었다.
*/

long long Ans, N, C, B;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	vector<int> A(N);
	for (int i = 0; i < N; i++)
		cin >> A[i];
	cin >> B >> C;
	for (auto& n : A) {
		if (n > B) {
			Ans += (n - B) / C;
			Ans += (n - B) % C ? 1 : 0;
		}
	}
	cout << Ans + N;
}