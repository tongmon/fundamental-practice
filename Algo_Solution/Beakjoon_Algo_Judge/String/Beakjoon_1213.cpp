#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1213
팰린드롬 만드는 문제인데 예외 고려를 안해서 좀 애먹었다.
AAABB 이렇게 주어지면 BAAAB 이것만 생각했지 ABABA는 생각하지 못했다.
사전순 출력이기에 이러한 사항을 고려해야 한다.
iterator 역순 출력 for문 표현법 까먹었는데 다시 기억하고 가자.
이 문제를 통해 예외 파악 능력을 길러간다.
*/

string S, A, P;
map<char, int> L;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> S;
	for (auto& c : S)
		L[c]++;
	for (auto& c : L) {
		if (c.second % 2) {
			if (!P.empty()) {
				cout << "I'm Sorry Hansoo";
				return 0;
			}
			P = c.first;
		}
		c.second /= 2;
		for (int i = 0; i < c.second; i++)
			A += c.first;
	}
	if (!P.empty())
		A += P;
	for (auto c = L.rbegin(); c != L.rend(); ++c) {
		for (int i = 0; i < c->second; i++)
			A += c->first;
	}
	cout << A;
}