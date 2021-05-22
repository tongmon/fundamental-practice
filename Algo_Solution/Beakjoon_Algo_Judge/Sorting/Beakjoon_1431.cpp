#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1431
간단한 정렬 문제다.
정렬 함수를 이용해서 풀면 된다.
*/

using pp = pair<string, int>;
int N;
vector<pp> C;

bool cmp(const pp& A, const pp& B) {
	if (A.first.length() != B.first.length())
		return A.first.length() < B.first.length();
	if (A.second != B.second)
		return A.second < B.second;
	return A.first < B.first;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++) {
		string a;
		cin >> a;
		int sum = 0;
		for (auto& A : a) {
			if ('0' <= A && A <= '9')
				sum += A - '0';
		}
		C.push_back({ a,sum });
	}
	sort(C.begin(), C.end(), cmp);
	for (auto& A : C)
		cout << A.first << '\n';
}