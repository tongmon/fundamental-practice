#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1269
집합 문제라 해쉬맵으로 접근했다.
*/

unordered_set<int> Oa, Ob, a, b, P;
int A, B, n;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> A >> B;
	for (int i = 0; i < A; i++) {
		cin >> n;
		Oa.insert(n);
	}
	for (int i = 0; i < B; i++) {
		cin >> n;
		Ob.insert(n);
	}
	a = Oa; b = Ob;
	for (auto& k : Ob) {
		if (a.find(k) != a.end())
			a.erase(a.find(k));
	}
	for (auto& k : Oa) {
		if (b.find(k) != b.end())
			b.erase(b.find(k));
	}
	for (auto& k : a) P.insert(k);
	for (auto& k : b) P.insert(k);
	cout << P.size();
}