#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/18119
비트마스킹과 해시맵을 사용하는 문제다.
비트마스킹이 처음엔 조금 까다로워도 하다 보면
굉장히 재밌는 기법인 것 같다. 강력하기도 하고...
이 문제에서 문자를 배열을 사용해서 검출하려하면
시간이 알파벳 개수인 26번이 필요하나 비트마스킹으로 on/off를 통해
알아내면 단 한번으로 끝난다.
이 문제를 통해 비트마스킹 실력을 늘려간다.
*/

unordered_map<int, int> Dic;
int N, M, a, Order;
char b;
string W;

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	Dic.reserve(20000);
	for (int i = 0; i < N; i++) {
		cin >> W;
		int Shif = 1 << 30;
		for (auto str : W) {
			int buf = 1 << (str - 'a');
			Shif |= buf;
		}
		if (Dic.find(Shif) == Dic.end())
			Dic[Shif] = 1;
		else
			Dic[Shif]++;
	}
	for (int i = 0; i < M; i++)
	{
		cin >> a >> b;
		int Word = 1 << (b - 'a');
		if (a == 1)
			Order |= Word;
		else
			Order ^= Word;
		int Cnt = 0;
		for (auto v : Dic) {
			if (!(v.first & Order))
				Cnt += v.second;
		}
		cout << Cnt << '\n';
	}
}