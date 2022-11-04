#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/11478
deque로 접근하면 더 빨라질까 했지만 아니였고 트리를 이용할 때 제일 빨라지는 문제였다.
나는 그냥 해쉬맵으로 접근했다.
*/

string A;
unordered_set<string> V;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> A;
	for (int i = 1; i <= A.size(); i++)
		for (int j = 0; j + i <= A.size(); j++)
			V.insert(A.substr(j, i));
	cout << V.size();
}