#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2941
스트링을 잘 끊어서 읽으면 되는 문제다.
substr을 이용하면 편하다.
*/

int k;
string A;
unordered_set<string> V;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> A;
	V.insert("c="); V.insert("c-"); V.insert("dz="); V.insert("d-");
	V.insert("lj"); V.insert("nj"); V.insert("s="); V.insert("z=");
	for (int i = 0; i < A.length(); i++) {
		if (i + 1 < A.length() && V.find(A.substr(i, 2)) != V.end())
			k++, i++;
		else if (i + 2 < A.length() && V.find(A.substr(i, 3)) != V.end())
			k++, i += 2;
		else k++;
	}
	cout << k;
}