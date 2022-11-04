#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2671
정규표현식 문제다.
정규표현식이기에 오토마타로 접근해도 되지만 regex라는 걸출한 라이브러리가 있어서
사용하였다.
이 문제를 통해 구현 능력을 길러간다.
*/

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	string A;
	cin >> A;
	regex R("((100+1+)|(01))+");
	cout << (regex_match(A, R) ? "SUBMARINE" : "NOISE");
}