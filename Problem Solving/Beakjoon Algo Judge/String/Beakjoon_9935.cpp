#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/9935
*/

string Input, Pat, Ans;

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> Input >> Pat;
	int K = 0;
	for (int i = 0; i < Input.size(); i++)
	{
		Ans.push_back(Input[i]);
		if (Input[i] == Pat.back()) {
			back:
			int j = Pat.size() - 1, k = Ans.size(); k--;
			while (j >= 0 && Ans.size() >= Pat.size()) {
				if (Pat[j] != Ans[k]) break;
				j--; k--;
			}
			if (j < 0) {
				j = 0;
				while (j < Pat.size()) {
					j++; Ans.pop_back();
				}
				goto back;
			}
		}
		if (!Ans.empty() && Ans.back() == Pat[0]) {
			int j = 1; string buf; i++;
			buf.push_back(Ans.back()); Ans.pop_back();
			while (j < Pat.size() && i < Input.size()) {

				buf.push_back(Input[i]);
				if (Pat[j] != Input[i]) break;
				i++; j++;
			}
			if (j != Pat.size()) {
				Ans += buf;
			}
			else i--;
		}
	}
	if (Ans.empty()) cout << "FRULA";
	else cout << Ans;
}