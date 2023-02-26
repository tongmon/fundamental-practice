#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1371
글자 수를 세면된다. 
문자열 받을 때만 getline 이용하고... 아니면 cin >> l 이렇게 하든지...
*/

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	string l;
	int A[27] = { 0, }, M = -1;
	while (getline(cin, l)) {
		for (auto& c : l) {
			if (c != ' ')
				M = max(M, ++A[c - 'a']);
		}
	}
	for (int i = 0; i < 27; i++)
		if (A[i] == M) cout << char(i + 'a');
}