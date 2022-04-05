#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/18511
완전탐색 문제.
재귀로 푸는게 보통 방식일 것이다.
한가지 최적화가 가능한데 밑의 내가 푼 풀이는 만약 123의 수를 만들 때
1 -> 1 + 2 * 10 -> 1 + 2 * 10 + 3 * 10 * 10 의 순서로 수를 만들고 있는데 이렇게 안하고
1 -> 1 * 10 + 2 -> (1 * 10 + 2) * 10 + 3 의 순서로 수를 만들게 된다면 밑 풀이의 재귀 함수 인자 수가 줄어든다.
*/

int n, k, q;
vector<int> a;

// 최적 풀이
void p(int y) {
	if (y > n) return;
	if (q < y) q = y;
	for (auto& c : a)
		p(c + y * 10);
}

// 나의 풀이
void f(int l, int p, int t) {
	if (q < p && p <= n)
		q = p;
	if (!l) return;
	for (auto& c : a)
		f(l - 1, p + c * t, 10 * t);
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> k;
	a.resize(k);
	for (int i = 0; i < k; i++)
		cin >> a[i];
	p(0);
	cout << q;
}