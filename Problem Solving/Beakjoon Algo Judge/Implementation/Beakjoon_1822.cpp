#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1822
set으로 접근 가능하지만 집합 연산을 지원하는 STL을 사용해봤다.
속도는 unordered_set 방식보다 집합 연산 STL set_difference가 월등히 빨랐다...
vector의 push_back을 편하게 수행하는 back_inserter 함수를 잘 알아놓자
*/

int A, B;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> A >> B;
	vector<int> p(A), k(B), a;
	for (int i = 0; i < A; i++)
		cin >> p[i];
	for (int i = 0; i < B; i++)
		cin >> k[i];
	sort(p.begin(), p.end());
	sort(k.begin(), k.end());
	set_difference(p.begin(), p.end(), k.begin(), k.end(), back_inserter(a));
	cout << a.size() << '\n';
	for (auto& n : a)
		cout << n << ' ';
}