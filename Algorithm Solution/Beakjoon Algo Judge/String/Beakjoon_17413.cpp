#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/17413
단어 뒤집기 문제.
< > 사이에 있는 문자열 빼고 다 뒤집으면 된다.
이 문제를 통해 구현속도를 늘려간다.
*/

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	string In, sub, Ans;
	getline(cin, In);
	bool k = 0;
	In += ' ';
	for (auto& s : In) {
		if (s == '<') {
			reverse(sub.begin(), sub.end());
			Ans += sub + s; k = 1;
			sub.clear();
		}
		else if (s == '>') {
			Ans += sub + s; k = 0;
			sub.clear();
		}
		else if (s == ' ') {
			if (!k)
				reverse(sub.begin(), sub.end());
			Ans += sub + s;
			sub.clear();
		}
		else
			sub += s;
	}
	cout << Ans;
}