#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1013
정규식을 사용하는 문제다.
DFA 즉 오토마타 그래프를 그려서도 해결할 수 있다고 하는데....
그냥 regex를 이용하여 풀었다.
이 문제를 통해 c++ 정규표현식 사용법과 오토마타에 대한 약간의 정보를 알았다.
*/

int T;
vector<string> A;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> T;
	vector<string> A(T);
	for (int i = 0; i < T; i++)
		cin >> A[i];
	regex R("((100+1+)|(01))+");
	for (auto& s : A) {
		cout << (regex_match(s, R) ? "YES\n" : "NO\n");
	}
}