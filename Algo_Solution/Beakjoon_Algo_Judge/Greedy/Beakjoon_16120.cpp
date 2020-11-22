#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/16120
PPAP 문제인데 문제에서는 P를 PPAP로 변환한 긴 문자열을 제공하지만
그게 PPAP 문자열인지 판단하는 경우에는 반대로 PPAP를 찾았다면 P로 바꾸어 주면 된다.
A가 나온 시점을 기준으로 그 다음 문자가 P인지 확인하고 이렇게 AP가 나왔다면
현재 입력된 문자들이 저장된 Buf에서 PP가 들어있는지 확인하고 맞다면 P를 하나 제거해
PPAP --> P 로 바꾸는 작업을 반복한다.
마지막에 Buf에 P만 남아있다면 PPAP 문자열인것이고 아니면 NP인 것이다.
약간 그리디와 스택 유형이 섞인 문제였다.
이 문제를 통해 그리디 문제에 대한 감을 키워나간다.
*/

string PPAP, Buf;

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> PPAP;
	if (PPAP.back() == 'A') {
		cout << "NP"; return 0;
	}
	for (int i = 0; i < PPAP.size(); i++)
	{
		if (PPAP[i] == 'A') {
			if (PPAP[++i] == 'P' && Buf.size() > 1) {
				Buf.pop_back();
			}
			else {
				cout << "NP"; return 0;
			}
		}
		else Buf.push_back('P');
	}
	if (Buf.size() == 1) cout << "PPAP";
	else cout << "NP";
}