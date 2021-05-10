#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1427
역정렬을 알면 풀 수 있는 문제다.
*/

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	string a;
	cin >> a;
	sort(a.begin(), a.end(), greater<char>());
	cout << a;
}
