#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2812
*/

string A, Ans;
int N, K;

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> K >> A;
	for (auto str : A) {
		while (K && !Ans.empty() && str > Ans.back()) {
			K--; Ans.pop_back();
		}
		Ans.push_back(str);
	}
	for (int i = 0; i < Ans.size() - K; i++)
		cout << Ans[i];
}