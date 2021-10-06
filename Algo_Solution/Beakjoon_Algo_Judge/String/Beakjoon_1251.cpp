#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1251
substr을 사용하면 편하다. 단지 시간복잡도가 높아질 뿐...
*/

string A;
vector<string> B;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> A;
	for (int i = 1; i < A.size() - 1; i++)
		for (int j = i; j < A.size() - 1; j++) {
			string P[3];
			P[0] = A.substr(0, i), P[1] = A.substr(i, j - i + 1), P[2] = A.substr(j + 1);
			for (int k = 0; k < 3; k++)
				reverse(P[k].begin(), P[k].end());
			B.push_back(P[0] + P[1] + P[2]);
		}
	sort(B.begin(), B.end());
	cout << B[0];
}