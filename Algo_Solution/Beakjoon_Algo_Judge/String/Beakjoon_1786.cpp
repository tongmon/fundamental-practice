#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1786
KMP 알고리즘을 알고 있는지 묻는 문제이다.
KMP 알고리즘에 대한 테크닉은 따로 만들어 올린 것이 있으므로
설명은 테크닉 폴더를 참고하기 바란다.
이렇게 접미사, 접두사 배열을 만들고 매칭시키는 매커니즘을 알아두고 잘 써먹자!
*/

string INFO, Pat;
vector<int> lps, Ans;
int Patsize, Cnt;

void lps_maker() {
	Patsize = Pat.size(); int j = 0;
	lps.reserve(Patsize); lps.push_back(0);
	for (int i = 1; i < Patsize; i++)
	{
		while (j > 0 && Pat[j] != Pat[i]) {
			j = lps[j - 1];
		}
		if (Pat[j] == Pat[i]) {
			lps.push_back(++j);
		}
		else lps.push_back(0);
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	getline(cin, INFO); getline(cin, Pat);
	lps_maker();
	for (int i = 0, j = 0; i < INFO.size(); i++)
	{
		while (j > 0 && Pat[j] != INFO[i]) {
			j = lps[j - 1];
		}
		if (Pat[j] == INFO[i]) {
			if (j == Patsize - 1) {
				Ans.push_back(i - j + 1);
				j = lps[j]; Cnt++;
			}
			else j++;
		}
	}
	cout << Cnt << '\n';
	for (auto Num : Ans) {
		cout << Num << ' ';
	}
}