#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1062
비트마스킹 문제다.
bitset을 이용하면 풀이가 용이해진다.
풀다가 실수한 점이 있었는데 size()에서 양수를 빼면 언더플로우가 발생한다는 점을
간과하고 계속 outofbound 오류의 원인을 찾고 있었다.
되도록이면 size()를 이용할 때 (int) 형변환을 붙이는 습관을 들이자.
이 문제를 통해 구현 속도를 늘려간다.
*/

using bit = bitset<26>;
int N, M, Max;
bit A, P;
vector<bit> Con;
vector<char> let;
string k;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	Con.resize(N);
	k = "antic";
	for (auto& l : k)
		A[l - 'a'] = 1;
	P = A;
	for (auto& bi : Con) {
		cin >> k;
		for (int i = 0; i < k.length(); i++) {
			if (!P[k[i] - 'a']) {
				P[k[i] - 'a'] = 1;
				let.push_back(k[i]);
			}
			bi[k[i] - 'a'] = 1;
		}
	}
	M -= 5;
	if (M < 0) {
		cout << 0; return 0;
	}
	vector<int> sel(let.size(), 1);
	for (int i = 0; i < (int)let.size() - M; i++)
		sel[i] = 0;
	do {
		bit B = A;
		for (int i = 0; i < sel.size(); i++) {
			if (sel[i])
				B[let[i] - 'a'] = 1;
		}
		int cnt = 0;
		for (auto& c : Con) {
			if ((B & c) == c)
				cnt++;
		}
		Max = max(Max, cnt);
	} while (next_permutation(sel.begin(), sel.end()));
	cout << Max;
}