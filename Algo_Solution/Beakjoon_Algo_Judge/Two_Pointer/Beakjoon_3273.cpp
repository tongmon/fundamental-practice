#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/3273
해쉬맵을 사용해서 풀었다.
두 쌍의 합이 특정 수를 만족하면 되는데 주의할 점은
24 = 12 + 12 이렇게 딱 반으로 쪼개지는 경우를 제외해야 한다.
이 문제를 통해 구현속도를 늘려간다.
*/

int N, T, a, t;
unordered_map<int, int> A;

int main() 
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N; 
	vector<int> B(N);
	for (int i = 0; i < N; i++) {
		cin >> a;
		A[a] = 0;
		B[i] = a;
	}
	cin >> T;
	for (int i = 0; i < N; i++) {
		if (A.find(T - B[i]) != A.end() && !A[B[i]] && !A[T - B[i]] && T != 2 * B[i]) {
			A[B[i]] = A[T - B[i]] = 1; t++;
		}
	}
	cout << t;
}