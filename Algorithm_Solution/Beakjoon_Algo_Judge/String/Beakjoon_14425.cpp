#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/14425
트라이를 이용하는 문제라곤 하는데 해쉬맵을 이용하는게 훨씬 빨라보여서
그렇게 구현했다.
이 문제를 통해 구현속도를 늘려간다.
*/

int N, M, Cnt;
string In;
unordered_set<string> A;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	A.reserve(10002);
	for (int i = 0; i < N; i++) {
		cin >> In;
		A.insert(In);
	}
	for (int i = 0; i < M; i++) {
		cin >> In;
		if (A.find(In) != A.end())
			Cnt++;
	}
	cout << Cnt;
}