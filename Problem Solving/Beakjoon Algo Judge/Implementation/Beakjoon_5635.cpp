#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/5635
년도에 가중치를 제일 크게, 그 다음 월, 그 다음 일 순으로 계산하면 된다.
*/

struct P {
	string N;
	int y, m, d;
};

bool operator<(P& a, P& b) {
	return a.y * 400 + a.m * 30 + a.d > b.y * 400 + b.m * 30 + b.d;
}

int t;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> t;
	vector<P> v;
	for (int i = 0; i < t; i++)
	{
		P k;
		cin >> k.N >> k.d >> k.m >> k.y;
		v.push_back(k);
	}
	sort(v.begin(), v.end());
	cout << v[0].N << "\n" << v.back().N;
}