#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/12871
문자열 매칭 문제다.
정규식으로 접근이 가능하지만 정규식을 매칭할 문자열을 구성하는 것이 중요하다.
abab
ababab
이러한 문자열은 무한번 더했을 경우 서로 같다고 볼 수 있는데
길이가 각각 4, 6 이기에 길이 4짜리를 6번 더한 문자열에서 정규식 매칭을 시도해야 한다.
*/

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	string A, B, C;
	cin >> A >> B;
	if (A.size() < B.size())
		swap(A, B);
	for (int i = 0; i < B.size(); i++)
		C += A;
	B = "(" + B + ")+";
	cout << regex_match(C, regex(B));
}